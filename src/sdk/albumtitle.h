#ifndef ALBUMTITLE_H
#define ALBUMTITLE_H

#include <QWidget>

class QLabel;
class QPushButton;
class AlbumTitle : public QWidget
{
    Q_OBJECT
public:
    explicit AlbumTitle(QWidget *parent = 0);
    //设置标题显示文字
    void setTitle(const QString &title);
    //获取左侧按钮指针
    QPushButton *leftButton() const;
    //获取右侧按钮指针
    QPushButton *rightButton() const;

signals:

public slots:

private:
    QLabel *m_title; //相册的标题Label
    QPushButton *m_left, *m_right; //左右侧按钮
};

#endif // ALBUMTITLE_H
