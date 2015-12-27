#include "albumbadimagechecker.h"
#include "albummodel.h"

#include "albumbadimagepicker.h"

#include <QDebug>

AlbumBadImagePicker::AlbumBadImagePicker(QObject *parent) :
    QObject(parent),
    m_albumModel(nullptr)
{
    //连接处理消息和处理槽
    connect(this, &AlbumBadImagePicker::processNext,
            this, &AlbumBadImagePicker::onActionProcessNext,
            Qt::QueuedConnection);
}

void AlbumBadImagePicker::addChecker(AlbumBadImageChecker *checker)
{
    //Reset checker parent relationship.
    checker->setParent(this);
    //Add to checker list.
    m_checkerList.append(checker);
}

void AlbumBadImagePicker::addPixmap(const QString &pixmapPath)
{
    //将Index添加到List中。
    m_checkPixmapList.append(QPixmap(pixmapPath));
    //启动工作线程.
    emit processNext();
}

void AlbumBadImagePicker::setModel(AlbumModel *model)
{
    m_albumModel=model;
    connect(this, &AlbumBadImagePicker::requireAppendRow,
            m_albumModel, &AlbumModel::appendRow,
            Qt::QueuedConnection);
}

void AlbumBadImagePicker::onActionProcessNext()
{
    //检查队列是否为空.
    if(m_checkPixmapList.isEmpty())
    {
        //结束
        return;
    }
    //获取第一个index
    QPixmap currentPixmap=m_checkPixmapList.takeFirst();
    //判定图像是否有问题
    bool badImage=checkImage(currentPixmap);
    //添加图片
    emit requireAppendRow(currentPixmap, badImage);
    //处理下一个.
    emit processNext();
}

inline bool AlbumBadImagePicker::checkImage(const QPixmap &pixmap)
{
    //使用所有的checker检查图片
    for(auto i : m_checkerList)
    {
        if(i->isImageBad(pixmap))
        {
            return true;
        }
    }
    //经过所有的检查没有问题。
    return false;
}
