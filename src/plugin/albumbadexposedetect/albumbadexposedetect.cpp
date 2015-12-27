#include <QLabel>

#include "mainwindow.h"
#include <QImage>
#include <QColor>
#include <QDebug>

#include "math.h"

#define EXPOSE (7.0)//曝光阈值
#define STANDARD (30.0)//标准差阈值
#define LIGHTNESS_LOW 60 //低亮度阈值
#define LIGHTNESS_HIGH 180//高亮度阈值

#include "albumbadexposedetect.h"

AlbumBadExposeDetect::AlbumBadExposeDetect(QObject *parent) :
    AlbumBadImageChecker(parent)
{
}

bool AlbumBadExposeDetect::isImageBad(const QPixmap &pixmap)
{
    //当图片无效略去判定
    if(pixmap.isNull())
    {
        return false;
    }
    //把图片尺寸改为300*300
    QImage originalImage = pixmap.scaled(300,
                                         300,
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation).toImage();
    //统计亮度
    int colorCount[256]={0};
    for(int x=0;x<300;x++)
    {
        for(int y=0;y<300;y++)
        {
            ++colorCount[QColor(originalImage.pixel(x,y)).value()];
        }
    }
    qreal colorProbablity[256],
            imageEntropy=0.0, //图像熵
            standard=0.0; //亮度标准差
    int colorAverage=0; //亮度平均值
    //计算图像熵、亮度标准差
    for(int i=0;i<256;++i)
    {
        colorProbablity[i]=(qreal)colorCount[i]/90000.0; //亮度概率
        if(colorCount[i]>0)
        {
            imageEntropy+=colorProbablity[i]*(log(1.0/colorProbablity[i])/log(2));
        }
        colorAverage+=colorCount[i]*i;
    }
    colorAverage/=90000;
    for(int i=0; i<256; ++i)
    {
        standard += colorProbablity[i]*((i-colorAverage)*(i-colorAverage));
    }
    standard=sqrt(standard);
    //根据阈值判定曝光
    qDebug()<<standard;
    if(standard>STANDARD)
    {
        qDebug()<<imageEntropy;
        return imageEntropy<EXPOSE;
    }
    return (colorAverage<LIGHTNESS_LOW || colorAverage>LIGHTNESS_HIGH);
}

