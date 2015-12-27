#ifndef ALBUMBADIMAGECHECKER_H
#define ALBUMBADIMAGECHECKER_H

#include <QObject>

class AlbumBadImageChecker : public QObject
{
    Q_OBJECT
public:
    //每一种情况继承一次该类，并重写isImageBad函数。
    AlbumBadImageChecker(QObject *parent = 0):QObject(parent){}

    //对于每一种不同的情况，判定该图像为差图像。
    //如果是差图像，那么返回true，反之，返回false。
    virtual bool isImageBad(const QPixmap &pixmap)=0;
};

#endif // ALBUMBADIMAGECHECKER_H
