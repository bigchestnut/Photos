#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QBoxLayout;
class AlbumListContent;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QWidget *m_container;

    AlbumListContent *m_albumList;

};

#endif // MAINWINDOW_H
