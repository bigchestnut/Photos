#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QPixmap>

#include <QList>

#include <QAbstractListModel>

class AlbumListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AlbumListModel(QObject *parent = 0);

    void appendRow(const QString &name,
                   const QPixmap &albumThumbs=QPixmap());

    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    QPixmap albumThumbs(int row) const;

    QString albumName(int row) const;

signals:

public slots:

private:
    struct AlbumItem
    {
        QPixmap thumbs; //缩略图
        QString name;
        //!FIXME: 将相册的MOdel的指针放到这里，图片数量由其rowCount返回。
    };

    QList<AlbumItem> m_albumList;
};

#endif // ALBUMLISTMODEL_H
