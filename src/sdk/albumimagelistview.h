#ifndef ALBUMIMAGELISTVIEW_H
#define ALBUMIMAGELISTVIEW_H

#include <QAbstractItemView>

class AlbumModel;
class AlbumProxyModel;
class AlbumImageListView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit AlbumImageListView(QWidget *parent = 0);

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

//    bool event(QEvent *event);

    void resizeEvent(QResizeEvent *event);

    void updateGeometries();

private:
    inline QRect itemContentRect(const QModelIndex &index) const;
    inline int indexScrollBarValue(const QModelIndex &index,
                                   QAbstractItemView::ScrollHint hint);
    int m_maxColumnCount, m_itemSize, m_spacing, m_itemSpacingSize, m_lineCount,
        m_baseItemSize;

    AlbumProxyModel *m_proxyModel;
    AlbumModel *m_model;
};

#endif // ALBUMIMAGELISTVIEW_H
