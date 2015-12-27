#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>

#include "albumglobal.h"

#include "albumtitle.h"

AlbumTitle::AlbumTitle(QWidget *parent) :
    QWidget(parent),
    m_title(new QLabel(this)),
    m_left(new QPushButton(this)),
    m_right(new QPushButton(this))
{
    qreal margins=22.0*albumGlobal->dpiMultiplyer();
    setContentsMargins(margins,margins,margins,margins);
    m_left->setStyleSheet("border:none");
    m_right->setStyleSheet("border:none");

    QFont titleFont=font();
    titleFont.setBold(true);
    m_title->setFont(titleFont);

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

