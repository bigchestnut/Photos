#ifndef ALBUMGLOBAL_H
#define ALBUMGLOBAL_H

#include <QObject>

//使用albumGlobal代替全局指针调用。能大幅度缩短代码长度。
#define albumGlobal (AlbumGlobal::instance())

class AlbumGlobal : public QObject
{
    Q_OBJECT
public:
    //获取该实例的全局指针
    static AlbumGlobal *instance();

    //该函数由一个全局函数（在MainWindow或者main函数）中调用一次。
    //将其初始化。此函数仅在程序开始运行时被调用一次。
    static void initial(QObject *parent);

    //获取DPI缩放倍数
    qreal dpiMultiplyer() const;

signals:

public slots:

private:
    static AlbumGlobal *m_instance; //单例类指针
    explicit AlbumGlobal(QObject *parent = 0); //构造函数
    AlbumGlobal(const AlbumGlobal &); //将拷贝构造函数设为私有，防止拷贝。
                                      //即不允许使用=复制该类。

    qreal m_dpiMultiplyer; //DPI缩放倍数
};

#endif // ALBUMGLOBAL_H
