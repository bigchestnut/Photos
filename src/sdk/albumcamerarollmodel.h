#ifndef ALBUMCAMERAROLLMODEL_H
#define ALBUMCAMERAROLLMODEL_H

#include "albumproxymodel.h"

#include <QObject>

class AlbumCameraRollModel : public AlbumProxyModel
{
    Q_OBJECT
public:
    explicit AlbumCameraRollModel(QObject *parent = 0);

signals:

public slots:
};

#endif // ALBUMCAMERAROLLMODEL_H
