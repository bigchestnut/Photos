#include <QBoxLayout>

#include "albumlistcontent.h"
#include "albumglobal.h"

#include "plugin/albumbadexposedetect/albumbadexposedetect.h"

#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_container(new QWidget(this)),
    m_albumList(new AlbumListContent(this))
{
#ifdef Q_OS_ANDROID
    setWindowState(Qt::WindowFullScreen);
#endif
    setContentsMargins(0,0,0,0);
    setCentralWidget(m_container);

    //添加检测器
    m_albumList->addChecker(new AlbumBadExposeDetect);

    //设置容器
    m_container->setContentsMargins(0,0,0,0);
    //设置Layout.
    QBoxLayout *containerLayout=new QBoxLayout(QBoxLayout::TopToBottom,
                                               m_container);
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->setSpacing(0);
    //添加控件到Layout
    containerLayout->addWidget(m_albumList, 1);

    //启动工作线程
    m_albumList->startWorkingThread();
}
