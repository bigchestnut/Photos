#include <QPushButton>
#include <QBoxLayout>

#include "albumtitle.h"
#include "albumlistmodel.h"
#include "albumlistview.h"

#include "albumlistcontent.h"

AlbumListContent::AlbumListContent(QWidget *parent) :
    QWidget(parent),
    m_title(new AlbumTitle(this)),
    m_albumView(new AlbumListView(this)),
    m_albumModel(new AlbumListModel(this))
{
    setContentsMargins(0,0,0,0);
    //设置Layout
    QBoxLayout *contentLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);
    setLayout(contentLayout);
    //添加标题栏
    contentLayout->addWidget(m_title);
    //添加相册列表
    contentLayout->addWidget(m_albumView, 1);

    //配置标题栏
    m_title->setTitle("相簿");
    m_title->leftButton()->setText("添加");
    m_title->rightButton()->setText("编辑");

    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");
    m_albumModel->appendRow("相机胶卷");
    m_albumModel->appendRow("我的照片流");
    m_albumModel->appendRow("质量差的图像");

    m_albumView->setModel(m_albumModel);
}

