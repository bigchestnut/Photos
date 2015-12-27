#ifndef ALBUMLISTCONTENT_H
#define ALBUMLISTCONTENT_H

#include <QWidget>

class AlbumTitle;
class AlbumListView;
class AlbumListModel;
class AlbumModel;
class AlbumCameraRollModel;
class AlbumBadImageModel;
class AlbumListContent : public QWidget
{
    Q_OBJECT
public:
    explicit AlbumListContent(QWidget *parent = 0);

signals:

public slots:

private:
    AlbumTitle *m_title;
    AlbumListView *m_albumView;
    AlbumListModel *m_albumModel;
    AlbumModel *m_imageModel;
    AlbumCameraRollModel *m_cameraRollModel;
    AlbumBadImageModel *m_badImageModel;
};

#endif // ALBUMLISTCONTENT_H
