#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QPixmap>
#include <QList>

#include <QAbstractListModel>

class AlbumProxyModel;
class AlbumListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AlbumListModel(QObject *parent = 0);

    void appendRow(const QString &name,
                   AlbumProxyModel *model=nullptr);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    QPixmap albumThumbs(int row) const;

    QString albumName(int row) const;

    AlbumProxyModel *albumModel(int row) const;

    int albumRowCount(int row) const;

signals:

public slots:

private:
    struct AlbumItem
    {
        QString name;
        AlbumProxyModel *model;
        AlbumItem() :
            name(QString()),
            model(nullptr)
        {
        }
    };

    QList<AlbumItem> m_albumList;
};

#endif // ALBUMLISTMODEL_H
