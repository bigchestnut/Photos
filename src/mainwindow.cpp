#include "albumlistcontent.h"

#include <QBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_container(new QWidget(this)),
    m_albumList(new AlbumListContent(this))
{
    setContentsMargins(0,0,0,0);
    setCentralWidget(m_container);
    //设置容器
    m_container->setContentsMargins(0,0,0,0);
    //设置Layout.
    QBoxLayout *containerLayout=new QBoxLayout(QBoxLayout::TopToBottom,
                                               m_container);
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->setSpacing(0);
    //添加控件到Layout
    containerLayout->addWidget(m_albumList, 1);
}

