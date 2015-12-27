#ifndef ALBUMLISTVIEW_H
#define ALBUMLISTVIEW_H

#include <QAbstractItemView>

class AlbumListModel;
class AlbumListView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit AlbumListView(QWidget *parent = 0);

    //获取一个像素点对应的Index。
    QModelIndex indexAt(const QPoint &point) const;

    //滚动到一个指定的Index
    void scrollTo(const QModelIndex &index, ScrollHint hint);

    //返回一个Item的区域。
    QRect visualRect(const QModelIndex &index) const;

    void setModel(QAbstractItemModel *model);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

    int horizontalOffset() const;

    int verticalOffset() const;

    bool isIndexHidden(const QModelIndex &index) const;

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);

    QRegion visualRegionForSelection(const QItemSelection &selection) const;

    bool event(QEvent *event);

protected slots:
    void updateGeometries();

private:
    void dumpTouchEvent(QEvent *event);
    AlbumListModel *m_model;
    int m_itemHeight;
    int m_itemSpacing;
    int m_thumbsSize;
    int m_fontSize;
};

#endif // ALBUMLISTVIEW_H
