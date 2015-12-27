#include <QDir>
#include <QPushButton>
#include <QBoxLayout>
#include <QItemSelectionModel>
#include <QStandardPaths>

#include "albumtitle.h"
#include "albumlistmodel.h"
#include "albumlistview.h"
#include "albummodel.h"
#include "albumcamerarollmodel.h"
#include "albumbadimagemodel.h"
#include "albumbadimagepicker.h"
#include "albumglobal.h"
#include "albumimagelistview.h"
#include "albumimagefinder.h"

#include "albumlistcontent.h"

AlbumListContent::AlbumListContent(QWidget *parent) :
    QWidget(parent),
    m_title(new AlbumTitle(this)),
    m_albumView(new AlbumListView(this)),
    m_albumModel(new AlbumListModel(this)),
    m_imageModel(new AlbumModel(this)),
    m_cameraRollModel(new AlbumCameraRollModel(this)),
    m_badImageModel(new AlbumBadImageModel(this)),
    m_finder(new AlbumImageFinder),
    m_picker(new AlbumBadImagePicker),
    m_imageListView(new AlbumImageListView(this)),
    m_notInitial(true)
{
    setContentsMargins(0,0,0,0);
    //设置Album Model到picker.
    m_picker->setModel(m_imageModel);
    connect(m_finder, &AlbumImageFinder::findFile,
            m_picker, &AlbumBadImagePicker::addPixmap,
            Qt::QueuedConnection);

    //设置Layout
    QBoxLayout *contentLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);
    setLayout(contentLayout);
    //添加标题栏
    contentLayout->addWidget(m_title);
    //添加相册列表
    contentLayout->addWidget(m_albumView, 1);
    //设置字体
    QFont titleFont=font();
    titleFont.setPixelSize(22*albumGlobal->dpiMultiplyer());
    setFont(titleFont);

    //配置标题栏
    m_title->setTitle("相簿");
    m_title->setFont(titleFont);
    m_title->leftButton()->setText("添加");
    m_title->leftButton()->setFont(titleFont);
    m_title->rightButton()->setText("编辑");
    m_title->rightButton()->setFont(titleFont);
    //配置各个代理Model
    m_cameraRollModel->setSourceModel(m_imageModel);
    m_badImageModel->setSourceModel(m_imageModel);

    m_albumModel->appendRow("相机胶卷", m_cameraRollModel);
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像", m_badImageModel);

    m_albumView->setModel(m_albumModel);
    connect(m_albumView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &AlbumListContent::onActionShowAlbum);

    m_imageListView->hide();
}

AlbumListContent::~AlbumListContent()
{
    //停止工作线程.
    m_pickerThread.quit();
    m_pickerThread.wait();

    //结束运行。
    m_picker->deleteLater();
    m_finder->deleteLater();
}

void AlbumListContent::addChecker(AlbumBadImageChecker *checker)
{
    m_picker->addChecker(checker);
}

void AlbumListContent::startWorkingThread()
{
    //移动到工作线程
    m_picker->moveToThread(&m_pickerThread);
    m_finder->moveToThread(&m_pickerThread);
    //启动工作线程
    m_pickerThread.start();
}

void AlbumListContent::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_imageListView->resize(m_albumView->size());
    m_imageListView->move(m_albumView->pos());
}

void AlbumListContent::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    //检查初始化Flag.
    if(m_notInitial)
    {
        //移除Flag
        m_notInitial=false;
        //设置所有目录.
        QStringList targetPaths;
        QFileInfo systemPictures=QFileInfo(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
        targetPaths.append(systemPictures.absoluteDir().path()+"/DCIM/Camera");

        //向Finder里添加目录.
        m_finder->analysisPaths(targetPaths);
    }
}

void AlbumListContent::onActionShowAlbum(const QModelIndex &index)
{
    //设置显示模型
    m_imageListView->setModel(m_albumModel->albumModel(index.row()));
    //显示相册
    m_imageListView->show();
}
