#include <QPainter>
#include <QScrollBar>

#include "albumglobal.h"
#include "albummodel.h"
#include "albumproxymodel.h"

#include "albumimagelistview.h"

AlbumImageListView::AlbumImageListView(QWidget *parent) :
    QAbstractItemView(parent),
    m_maxColumnCount(0),
    m_itemSize(90),
    m_spacing(2),
    m_itemSpacingSize(107),
    m_lineCount(0),
    m_baseItemSize(50),
    m_proxyModel(nullptr)
{
    //根据DPI重新计算大小
    m_baseItemSize=110.0*albumGlobal->dpiMultiplyer();
    m_spacing=2.0*albumGlobal->dpiMultiplyer();

    //Set the vertical scroll bar style.
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 0);"
                                       "   width: 8px;"
                                       "}"
                                       "QScrollBar::handle:vertical {"
                                       "   background: rgba(100, 100, 100);"
                                       "   min-height: 10px;"
                                       "   border-radius: 4px;"
                                       "}"
                                       "QScrollBar::add-line:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 100);"
                                       "   height: 0px;"
                                       "   subcontrol-position: down;"
                                       "   subcontrol-origin: margin;"
                                       "}"
                                       "QScrollBar::sub-line:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 100);"
                                       "   height: 0px;"
                                       "   subcontrol-position: up;"
                                       "   subcontrol-origin: margin;"
                                       "}");
}

QModelIndex AlbumImageListView::indexAt(const QPoint &point) const
{
    //Calculate the point content position and the line of the point.
    int pointContentY=verticalScrollBar()->value()+point.y(),
            itemLine=pointContentY/m_itemSpacingSize;
    //Check whether mouse click on a row spacing part.
    if(pointContentY-itemLine*m_itemSpacingSize<m_spacing)
    {
        return QModelIndex();
    }
    //Calculate the column of the position.
    int itemColumn=point.x()/m_itemSpacingSize,
            pointXInItem=point.x()-itemColumn*m_itemSpacingSize;
    //Check whether mouse click on a column spacing part.
    if(pointXInItem<m_spacing || pointXInItem>m_spacing+m_itemSize)
    {
        return QModelIndex();
    }
    //Calculate the item category index.
    int categoryRow=itemLine*m_maxColumnCount+itemColumn;
    //Check if the category row vaild.
    //We should check the category proxy model, because the point is a display
    //variable.
    return (categoryRow>-1 && categoryRow<m_proxyModel->rowCount())?
                m_proxyModel->index(categoryRow, 0, rootIndex()):
                QModelIndex();
}

void AlbumImageListView::scrollTo(const QModelIndex &index,
                                  QAbstractItemView::ScrollHint hint)
{
    //Check the index and the max column count.
    if(!index.isValid() || m_maxColumnCount==0 ||
            //Check whether we need to move the vertical scroll bar.
            (hint==QAbstractItemView::EnsureVisible &&
             rect().contains(visualRect(index), true)))
    {
        return;
    }
    //Use timeline to move to the position.
    verticalScrollBar()->setValue(indexScrollBarValue(index, hint));
    //Update.
    viewport()->update();
}

QRect AlbumImageListView::visualRect(const QModelIndex &index) const
{
    //Get the item content rect.
    QRect indexRect=itemContentRect(index);
    //If the rect is vaild, remove the value of the scroll bar to get the
    //position in the rect.
    return indexRect.isValid()?
                QRect(indexRect.left()-horizontalScrollBar()->value(),
                      indexRect.top()-verticalScrollBar()->value(),
                      indexRect.width(),
                      indexRect.height()):
                QRect();
}

void AlbumImageListView::setModel(QAbstractItemModel *model)
{
    //Save the proxy model and the category model.
    m_proxyModel=static_cast<AlbumProxyModel *>(model);
    //Check out the proxy model.
    if(m_proxyModel==nullptr)
    {
        return;
    }
    //Get the album model.
    m_model=static_cast<AlbumModel *>(m_proxyModel->sourceModel());
    //Set the model.
    QAbstractItemView::setModel(m_proxyModel);
    //Update the geometries.
    updateGeometries();
}

void AlbumImageListView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(viewport());

    painter.setRenderHints(QPainter::Antialiasing |
                               QPainter::TextAntialiasing,
                               true);

    //Check if we need to paint the background.
    if(autoFillBackground())
    {
        painter.fillRect(rect(), viewOptions().palette.base());
    }

    //Check the model first.
    if(m_proxyModel==nullptr)
    {
        return;
    }
    //Get the row count.
    int albumCount=m_proxyModel->rowCount();
    //Check the album count first.
    if(albumCount==0)
    {
        return;
    }
    //Calculate the line count.
    m_lineCount=(albumCount+m_maxColumnCount-1)/m_maxColumnCount;
    //Generate the parameters.
    int currentColumn=0,
            currentLeft=m_spacing,
            currentLine=verticalScrollBar()->value()/m_itemSpacingSize,
            currentTop=m_spacing+currentLine*m_itemSpacingSize,
            currentRow=currentLine*m_maxColumnCount,
            heightSurplus=height()+m_itemSpacingSize;
    //Change the origin of coordinate.
    painter.translate(0, -verticalScrollBar()->value());
    //Draw all the albums, until there's no album left, no height surplus.
    while(currentRow < albumCount && heightSurplus > 0)
    {
        //Get the source index of the item.
        QModelIndex &&proxyIndex=m_proxyModel->index(currentRow, 0);
        //Draw the album.
        painter.drawPixmap(
                    currentLeft,
                    currentTop,
                    proxyIndex.data(
                        Qt::DecorationRole).value<QPixmap>().scaled(
                        m_itemSize,
                        m_itemSize,
                        Qt::IgnoreAspectRatio,
                        Qt::SmoothTransformation));
        //Add current row to the next album model row.
        ++currentRow;
        //Add current column to the next position.
        ++currentColumn;
        //Check if we need to move to next row.
        if(currentColumn>=m_maxColumnCount)
        {
            //Add current line.
            ++currentLine;
            //Reset the column.
            currentColumn=0;
            //Change the position.
            currentLeft=m_spacing;
            currentTop+=m_itemSpacingSize;
            heightSurplus-=m_itemSpacingSize;
        }
        else
        {
            //Move to next column position.
            currentLeft+=m_itemSpacingSize;
        }
    }
    //Update the scroll bar value.
    updateGeometries();
}

QModelIndex AlbumImageListView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    //! FIXME: Add operation here.
    Q_UNUSED(cursorAction)
    Q_UNUSED(modifiers)
    return currentIndex();
}

int AlbumImageListView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

int AlbumImageListView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

bool AlbumImageListView::isIndexHidden(const QModelIndex &index) const
{
    //Treat all the index visible.
    Q_UNUSED(index)
    return false;
}

void AlbumImageListView::setSelection(
        const QRect &rect,
        QItemSelectionModel::SelectionFlags command)
{
    //Simply select the top left position.
    selectionModel()->select(indexAt(QPoint(rect.x(), rect.y())),
                             command);
}

QRegion AlbumImageListView::visualRegionForSelection(
        const QItemSelection &selection) const
{
    //If there's no selection, of course nothing.
    if(selection.size()==0)
    {
        return QRect();
    }
    //Add the only select item to the region, return the region.
    QItemSelectionRange range=selection.at(0);
    QRegion region;
    region+=visualRect(indexAt(QPoint(range.top(), range.left())));
    return region;
}

void AlbumImageListView::resizeEvent(QResizeEvent *event)
{
    //Resize the widget.
    QAbstractItemView::resizeEvent(event);
    //重新计算长宽
    m_maxColumnCount=width()/(m_baseItemSize+m_spacing);
    m_itemSize=width()/m_maxColumnCount-m_spacing;
    //Calcualte the spacing item width and height.
    m_itemSpacingSize=m_spacing+m_itemSize;
}

void AlbumImageListView::updateGeometries()
{
    //Update the range of the vertical scroll bar.
    verticalScrollBar()->setRange(0,
                                  qMax(0,
                                       m_lineCount*m_itemSpacingSize +
                                       m_spacing-height()));
    //Update the page and single step.
    verticalScrollBar()->setPageStep(m_itemSpacingSize>>2);
    verticalScrollBar()->setSingleStep(m_itemSpacingSize>>2);
}

inline QRect AlbumImageListView::itemContentRect(const QModelIndex &index) const
{
    //Check the index first.
    if(!index.isValid() || m_maxColumnCount==0)
    {
        return QRect();
    }
    //Calculate the item line.
    int itemLine=index.row()/m_maxColumnCount;
    //Calculate the rect.
    return QRect((index.row()-itemLine*m_maxColumnCount)*m_itemSpacingSize+
                 m_spacing,
                 itemLine*m_itemSpacingSize+m_spacing,
                 m_itemSize,
                 m_itemSize);
}

inline int AlbumImageListView::indexScrollBarValue(
        const QModelIndex &index,
        QAbstractItemView::ScrollHint hint)
{
    //Get the top of index position, set it to scroll value.
    int topPositionValue=index.row()/m_maxColumnCount*m_itemSpacingSize;
    //Change the item content Y according to the hint.
    switch(hint)
    {
    case QAbstractItemView::PositionAtTop:
        //No need to change.
        return topPositionValue;
    case QAbstractItemView::PositionAtCenter:
        //Reduce a half of the viewer height to move up.
        return topPositionValue-((height()-m_itemSpacingSize)>>1);
    case QAbstractItemView::PositionAtBottom:
        //Reduce the whole viewer height to move up.
        return topPositionValue-height()+m_itemSpacingSize;
        break;
    default:
        //Now, the index item must be a unvisible one in the viewer.
        //We have already has the top position, calculate the bottom position,
        //and calculate the distence of the current vertical scroll bar's value
        //to these two position.
        int bottomPositionValue=topPositionValue-height()+m_itemSpacingSize;
        //If to the bottom is lesser than to top, change the value.
        return (qAbs(verticalScrollBar()->value()-bottomPositionValue)<
                qAbs(verticalScrollBar()->value()-topPositionValue))?
                    bottomPositionValue:
                    topPositionValue;
    }
}
