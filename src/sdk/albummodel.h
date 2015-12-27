#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QPixmap>

#include <QAbstractListModel>

class AlbumBadImagePicker;
class AlbumModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AlbumModelRole
    {
        IsBadRole = Qt::UserRole
    };

    explicit AlbumModel(QObject *parent = 0);


    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

public slots:
    void appendRow(const QPixmap &pixmap, bool isBadImage);

private:
    struct ImageItem
    {
        //图片本身
        QPixmap pixmap;
        //质量差标签
        bool bad;
        //通过构造函数设置默认值
        //结构体的构造函数
        ImageItem() :
            pixmap(QPixmap()),
            bad(false)
        {
        }
    };

    //设置List保存所有的图片
    QList<ImageItem> m_imageList;

    int m_scaledSize;
};

#endif // ALBUMMODEL_H
