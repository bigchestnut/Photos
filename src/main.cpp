#include "mainwindow.h"
#include "sdk/albumglobal.h"
#include <QScreen>
#include <QFont>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //初始化全局变量
    AlbumGlobal::initial(&app);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
