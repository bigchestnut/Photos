#ifndef ALBUMPROXYMODEL_H
#define ALBUMPROXYMODEL_H

#include <QPixmap>

#include <QSortFilterProxyModel>

class AlbumProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AlbumProxyModel(QObject *parent = 0);

    QPixmap thumbs() const;
    void setThumbs(const QPixmap &thumbs);

signals:

public slots:

private:
    QPixmap m_thumbs;
};

#endif // ALBUMPROXYMODEL_H
