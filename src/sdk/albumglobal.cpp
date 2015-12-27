#include <QApplication>
#include <QScreen>

#include "albumglobal.h"

//初始化指针为null.
//该变量将在应用运行分配内存时被初始化。
AlbumGlobal *AlbumGlobal::m_instance=nullptr;

AlbumGlobal *AlbumGlobal::instance()
{
    return m_instance;
}

void AlbumGlobal::initial(QObject *parent)
{
    //检查全局变量是否已经指向一个可用的类。
    if(m_instance==nullptr)
    {
        m_instance=new AlbumGlobal(parent);
    }
}

AlbumGlobal::AlbumGlobal(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<QVector<int>>("QVector<int>");

    //计算DPI缩放倍数.
    //Get the screen.
    QScreen *screen = qApp->primaryScreen();
    //Calculate the multiplyer.
    m_dpiMultiplyer = screen->logicalDotsPerInch()/96.0;
}

qreal AlbumGlobal::dpiMultiplyer() const
{
    return m_dpiMultiplyer;
}
