#include "albumproxymodel.h"

#include "albumlistmodel.h"

AlbumListModel::AlbumListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

void AlbumListModel::appendRow(const QString &name,
                               AlbumProxyModel *model)
{
    //建立一个新的Item.
    AlbumItem item;
    item.name=name;
    item.model=model;
    //将Item添加到List中.
    beginInsertRows(QModelIndex(),
                    m_albumList.size(),
                    m_albumList.size()); //根据文档，你必须这么写.
    //将其添加到List尾部.
    m_albumList.append(item);
    endInsertRows(); //根据文档，你必须这么写.
}

int AlbumListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_albumList.size();
}

QVariant AlbumListModel::data(const QModelIndex &index, int role) const
{
    //对于所有不可用的Index，全部返回一个无效值。
    if(!index.isValid())
    {
        return QVariant();
    }
    //首先，获取List中对应的Item。
    const AlbumItem &albumItem=m_albumList.at(index.row());
    //根据不同的role（角色），返回对应的数据.
    switch(role)
    {
    case Qt::DecorationRole: //缩略图
        return albumItem.model==nullptr?
                    QPixmap():
                    albumItem.model->thumbs();
    case Qt::DisplayRole: //显示的文字  （会一直向下执行）
    case Qt::EditRole:    //当编辑文字启用时，显示的文字.
        return albumItem.name;
    default: //对于其他的信息，无需返回有效值。
        return QVariant();
    }
}

QPixmap AlbumListModel::albumThumbs(int row) const
{
    return m_albumList.at(row).model==nullptr?
                QPixmap():
                m_albumList.at(row).model->thumbs();
}

QString AlbumListModel::albumName(int row) const
{
    return m_albumList.at(row).name;
}

AlbumProxyModel *AlbumListModel::albumModel(int row) const
{
    return m_albumList.at(row).model;
}

int AlbumListModel::albumRowCount(int row) const
{
    return m_albumList.at(row).model==nullptr?
                0:
                m_albumList.at(row).model->rowCount();
}

