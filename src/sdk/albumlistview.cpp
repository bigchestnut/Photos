#include <QApplication>
#include <QPainter>
#include <QScrollBar>
#include <QGestureEvent>
#include <QTapGesture>

#include "albumlistmodel.h"
#include "albumglobal.h"

#include "albumlistview.h"

#include <QDebug>

AlbumListView::AlbumListView(QWidget *parent) :
    QAbstractItemView(parent),
    m_model(nullptr),
    m_itemHeight(107),
    m_itemSpacing(12),
    m_thumbsSize(82.5),
    m_fontSize(22)
{
    //获取DPI缩放倍数.
    qreal &&dpiMultiplyer=albumGlobal->dpiMultiplyer();
    //Scaled the parameters.
    m_itemHeight*=dpiMultiplyer;
    m_itemSpacing*=dpiMultiplyer;
    m_thumbsSize*=dpiMultiplyer;
    m_fontSize*=dpiMultiplyer;

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

    grabGesture(Qt::PanGesture);
}

QModelIndex AlbumListView::indexAt(const QPoint &point) const
{
    //判断是否存在Model.
    if(m_model==nullptr)
    {
        return QModelIndex();
    }
    /* ==============
     * |          | ^
     * |          |
     * +----------+
     * |          | *
     * |       *  |   该点的真实坐标：到当前显示的顶端距离+滚动条距离
     * +----------+
     * |          |
     * |          |
     * |          |
     * |          |
     * |          |
     * |          |
     * +----------+ V
     */
    //首先获取垂直滚动条的数值，获取该点的真实坐标，计算所在行.
    int itemRow=(point.y()+verticalScrollBar()->value())/m_itemHeight;
    //判断该行是否超过Model的最大值。
    return (itemRow<m_model->rowCount())?
                m_model->index(itemRow): //若有效，返回该行的Index。
                QModelIndex(); //否则，返回一个无效值。
}

void AlbumListView::scrollTo(const QModelIndex &index,
                             QAbstractItemView::ScrollHint hint)
{
    //判断Model是否存在，Index是否有效
    if((!m_model) || (!index.isValid()))
    {
        //无需额外操作
        return;
    }
    //计算Index的真实坐标.
    int itemTop=m_itemHeight*index.row();
    //再根据hint（位于顶部、位于底部、位于中间、只要显示即可），移动滚动条.
    switch(hint)
    {
    case QAbstractItemView::PositionAtTop:
        break;
    case QAbstractItemView::PositionAtCenter:
        itemTop-=((height()-m_itemHeight)>>1);
        break;
    case QAbstractItemView::PositionAtBottom:
        itemTop-=(height()-m_itemHeight);
        break;
    default:
    {
        //判断其是否已经显示在窗口上了。
        if(rect().contains(visualRect(index), true))
        {
            //无需进行其它操作。
            return;
        }
        //首先，计算如果让其在底部显示的高度.
        int itemBottom=itemTop-height()+m_itemHeight;
        //判断移动到顶部与移动到底部的距离，取二者中较小的一个.
        itemTop=(qAbs(verticalScrollBar()->value()-itemBottom)<
                 qAbs(verticalScrollBar()->value()-itemTop)?
                     itemBottom:itemTop);
        break;
    }
    }
    //改变滚动条的数值为itemTop.
    verticalScrollBar()->setValue(itemTop);
    //更新画布区域.
    viewport()->update();
}

QRect AlbumListView::visualRect(const QModelIndex &index) const
{
    //判断Model和Index是否有效.
    if((m_model==nullptr) || (!index.isValid()))
    {
        //返回一个无效值.
        return QRect();
    }
    //计算其真实坐标，减去垂直滚动条的数值.
    return QRect(0,
                 m_itemHeight*index.row()-verticalScrollBar()->value(),
                 width(),
                 m_itemHeight);
}

void AlbumListView::setModel(QAbstractItemModel *model)
{
    //设置Model指针
    m_model=static_cast<AlbumListModel *>(model);
    //调用原来Qt提供的setModel函数.
    QAbstractItemView::setModel(m_model);
    //检查Model指针是否有效
    if(m_model==nullptr)
    {
        //当指针为空，不需要额外处理.
        return;
    }
    //更新画面.
    updateGeometries();
}

void AlbumListView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //判断Model是否存在.
    if(m_model==nullptr)
    {
        return;
    }
    //构建一个Painter.
    QPainter painter(viewport());
    //设置反锯齿
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform, true);
    //计算第一个可以看到的row.
    int currentRow=verticalScrollBar()->value()/m_itemHeight,
        currentTop=currentRow*m_itemHeight;
    const int maximumTop=verticalScrollBar()->value()+height();
    //改变Painter的坐标系.
    painter.translate(0, -verticalScrollBar()->value());
    //设置Painter的字体.
    QFont widgetFont=font();
    widgetFont.setPixelSize(m_fontSize);
    painter.setFont(widgetFont);
    //绘制每一行的数据.
    while(currentRow<m_model->rowCount() && currentTop < maximumTop)
    {
        //检查当前值是否是选中的
        if(currentRow==currentIndex().row())
        {
            painter.fillRect(QRectF(0, currentTop, width(), m_itemHeight),
                             QColor(217, 217, 217));
        }
        //绘制左侧的缩略图
        painter.drawPixmap(m_itemSpacing,
                           currentTop+m_itemSpacing,
                           m_model->albumThumbs(currentRow));
        //绘制右侧的文字.
        painter.drawText((m_itemSpacing*3)+m_thumbsSize,
                         currentTop+(m_itemHeight>>1)-(m_itemSpacing>>1),
                         m_model->albumName(currentRow));
        //绘制照片数量.
        painter.drawText((m_itemSpacing*3)+m_thumbsSize,
                         currentTop+(m_itemHeight>>1)+(m_itemSpacing>>1)+
                         m_fontSize,
                         QString::number(m_model->albumRowCount(currentRow)));
        //移动到下一个Row.
        ++currentRow;
        currentTop+=m_itemHeight;
    }
}

void AlbumListView::gestureEvent(QGestureEvent *event)
{
    //检查event类型
    QGesture *gesture=event->gesture(Qt::TapGesture);
    if(gesture)
    {
        //检测到按下事件.
        tapGestureEvent(static_cast<QTapGesture *>(gesture));
        return;
    }
}

void AlbumListView::tapGestureEvent(QTapGesture *event)
{
    //对于点按事件，我们处理为单击
    showAlbum(event->position());
}

QModelIndex AlbumListView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                      Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction)
    Q_UNUSED(modifiers)
    //!FIXME: 添加根据上下键移动当前选择的功能.
    return QModelIndex();
}

int AlbumListView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

int AlbumListView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

bool AlbumListView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return false;
}

void AlbumListView::setSelection(const QRect &rect,
                                 QItemSelectionModel::SelectionFlags command)
{
    //简单的传递参数.
    selectionModel()->select(indexAt(QPoint(rect.topLeft())), command);
}

QRegion AlbumListView::visualRegionForSelection(const QItemSelection &selection) const
{
    //如果没有选中的区域，那么返回无效值.
    if(selection.size()==0)
    {
        return QRect();
    }
    //添加区域.
    QItemSelectionRange range=selection.at(0);
    QRegion region;
    region+=visualRect(indexAt(QPoint(range.left(),
                                      range.top())));
    return region;
}

bool AlbumListView::event(QEvent *event)
{
    //筛选出手势类型.
    switch(event->type())
    {
    case QEvent::Gesture:
        gestureEvent(static_cast<QGestureEvent *>(event));
        return true;
    default:
        //Do original event.
        return QAbstractItemView::event(event);
    }

}

void AlbumListView::updateGeometries()
{
    //首先检测Model是否有效.
    if(m_model==nullptr)
    {
        verticalScrollBar()->setRange(0, 0);
        return;
    }
    //更新右侧滚动条的范围.
    verticalScrollBar()->setRange(0,
                                  qMax(0,
                                       m_model->rowCount() * m_itemHeight
                                       - height()));
    //更新幅度.
    verticalScrollBar()->setPageStep(m_itemHeight);
    verticalScrollBar()->setSingleStep(m_itemHeight);
}

void AlbumListView::showAlbum(const QPointF &pos)
{
    //检查Index是否有效.
    QModelIndex index=indexAt(pos.toPoint());
    //选中特定的Item.
    if(index.isValid())
    {
        setCurrentIndex(index);
    }
}
