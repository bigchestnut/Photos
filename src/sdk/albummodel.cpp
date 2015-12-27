#include "albumbadimagepicker.h"
#include "albumglobal.h"

#include "albummodel.h"

#include <QDebug>

AlbumModel::AlbumModel(QObject *parent) :
    QAbstractListModel(parent),
    m_scaledSize(50)
{
    m_scaledSize=50.0*albumGlobal->dpiMultiplyer();
}

void AlbumModel::appendRow(const QPixmap &pixmap, bool isBadImage)
{
    //建立一个新的Item.
    ImageItem item;
    item.pixmap=pixmap.scaled(m_scaledSize,
                              m_scaledSize,
                              Qt::KeepAspectRatioByExpanding,
                              Qt::SmoothTransformation);
    item.bad=isBadImage;
    //添加到Model.
    //将Item添加到List中.
    beginInsertRows(QModelIndex(),
                    m_imageList.size(),
                    m_imageList.size()); //根据文档，你必须这么写.
    //将其添加到List尾部.
    m_imageList.append(item);
    endInsertRows(); //根据文档，你必须这么写.
}

int AlbumModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_imageList.size();
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    //首先判定index是否合法.
    if(!index.isValid())
    {
        return QVariant();
    }
    //根据index的row获取对应的图片结构体.
    const ImageItem &item=m_imageList.at(index.row());
    //根据角色返回对应的值
    switch(role)
    {
    case Qt::DecorationRole:
        return item.pixmap;
    case IsBadRole:
        return item.bad;
    default:
        return QVariant();
    }
}

bool AlbumModel::setData(const QModelIndex &index,
                         const QVariant &value,
                         int role)
{
    //首先判定index是否合法.
    if(!index.isValid())
    {
        return false;
    }
    //根据index的row获取对应的图片结构体.
    ImageItem item=m_imageList.at(index.row());
    //根据角色更改对应的值
    switch(role)
    {
    case Qt::DecorationRole:
        item.pixmap=value.value<QPixmap>();
        break;
    case IsBadRole:
        item.bad=value.toBool();
        break;
    default:
        break;
    }
    //保存新的数值
    m_imageList.replace(index.row(), item);
    //发射更新信号
    emit dataChanged(index, index);
    return true;
}
