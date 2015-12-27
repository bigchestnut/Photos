#ifndef ALBUMBADIMAGEPICKER_H
#define ALBUMBADIMAGEPICKER_H

#include <QPixmap>
#include <QList>

#include <QObject>

class AlbumModel;
class AlbumBadImageChecker;
class AlbumBadImagePicker : public QObject
{
    Q_OBJECT
public:
    explicit AlbumBadImagePicker(QObject *parent = 0);

    void addChecker(AlbumBadImageChecker *checker);
    void setModel(AlbumModel *model);

signals:
    void processNext();
    void requireAppendRow(const QPixmap &pixmap, bool isBad);

public slots:
    void addPixmap(const QString &pixmapPath);

private slots:
    void onActionProcessNext();

private:
    inline bool checkImage(const QPixmap &pixmap);
    QList<AlbumBadImageChecker *> m_checkerList;
    QList<QPixmap> m_checkPixmapList;
    AlbumModel *m_albumModel;
};

#endif // ALBUMBADIMAGEPICKER_H
