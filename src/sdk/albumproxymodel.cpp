#include "albumproxymodel.h"

AlbumProxyModel::AlbumProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_thumbs(QPixmap())
{
}

QPixmap AlbumProxyModel::thumbs() const
{
    return m_thumbs;
}

void AlbumProxyModel::setThumbs(const QPixmap &thumbs)
{
    m_thumbs = thumbs;
}
