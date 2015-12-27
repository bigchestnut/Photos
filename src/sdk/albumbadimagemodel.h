#ifndef ALBUMBADIMAGEMODEL_H
#define ALBUMBADIMAGEMODEL_H

#include "albumproxymodel.h"

class AlbumBadImageModel : public AlbumProxyModel
{
    Q_OBJECT
public:
    explicit AlbumBadImageModel(QObject *parent = 0);

signals:

public slots:

protected:
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;
};

#endif // ALBUMBADIMAGEMODEL_H
