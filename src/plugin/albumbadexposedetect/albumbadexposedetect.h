#ifndef ALBUMBADEXPOSEDETECT_H
#define ALBUMBADEXPOSEDETECT_H

#include "albumbadimagechecker.h"

class AlbumBadExposeDetect : public AlbumBadImageChecker
{
    Q_OBJECT
public:
    explicit AlbumBadExposeDetect(QObject *parent = 0);

    bool isImageBad(const QPixmap &pixmap);

signals:

public slots:

private:

};

#endif // ALBUMBADEXPOSEDETECT_H
