#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include "albumtitle.h"

AlbumTitle::AlbumTitle(QWidget *parent) :
    QWidget(parent),
    m_title(new QLabel(this)),
    m_left(new QPushButton(this)),
    m_right(new QPushButton(this))
{
    setContentsMargins(0,0,0,0);
    m_left->setStyleSheet("border:none");
    m_right->setStyleSheet("border:none");
    QBoxLayout *titleLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    titleLayout->addWidget(m_left);
    titleLayout->addStretch();
    titleLayout->addWidget(m_title);
    titleLayout->addStretch();
    titleLayout->addWidget(m_right);
    setLayout(titleLayout);
}

void AlbumTitle::setTitle(const QString &title)
{
    m_title->setText(title);
}

QPushButton *AlbumTitle::leftButton() const
{
    return m_left;
}

QPushButton *AlbumTitle::rightButton() const
{
    return m_right;
}

