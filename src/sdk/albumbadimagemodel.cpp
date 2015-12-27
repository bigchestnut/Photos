#include "albummodel.h"

#include "albumbadimagemodel.h"

AlbumBadImageModel::AlbumBadImageModel(QObject *parent) :
    AlbumProxyModel(parent)
{
}

bool AlbumBadImageModel::filterAcceptsRow(
        int source_row,
        const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent)
    //判定IsBad为true的时候，接受该行.
    return sourceModel()->data(sourceModel()->index(source_row, 0),
                               //使用IsBad直接判定。
                               AlbumModel::IsBadRole).toBool();
}

