#ifndef ALBUMLISTCONTENT_H
#define ALBUMLISTCONTENT_H

#include <QThread>

#include <QWidget>

class AlbumImageListView;
class AlbumBadImageChecker;
class AlbumTitle;
class AlbumListView;
class AlbumListModel;
class AlbumModel;
class AlbumCameraRollModel;
class AlbumBadImageModel;
class AlbumBadImagePicker;
class AlbumImageFinder;
class AlbumListContent : public QWidget
{
    Q_OBJECT
public:
    explicit AlbumListContent(QWidget *parent = 0);
    ~AlbumListContent();

    void addChecker(AlbumBadImageChecker *checker);

    void startWorkingThread();

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

    void showEvent(QShowEvent *event);

private slots:
    void onActionShowAlbum(const QModelIndex &index);

private:
    QThread m_pickerThread;
    AlbumTitle *m_title;
    AlbumListView *m_albumView;
    AlbumListModel *m_albumModel;
    AlbumModel *m_imageModel;
    AlbumCameraRollModel *m_cameraRollModel;
    AlbumBadImageModel *m_badImageModel;
    AlbumImageFinder *m_finder;
    AlbumBadImagePicker *m_picker;

    AlbumImageListView *m_imageListView;

    bool m_notInitial;
};

#endif // ALBUMLISTCONTENT_H
