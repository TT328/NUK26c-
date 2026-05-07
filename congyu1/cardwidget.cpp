#include "cardwidget.h"

#include <QPropertyAnimation>
#include <QIcon>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QCoreApplication>

CardWidget::CardWidget(int id,QWidget* parent)
    : QPushButton(parent),m_id(id)
{
    setFixedSize(120,160);
    setCursor(Qt::PointingHandCursor);

    setStyleSheet(
        "QPushButton{"
        "background:rgba(255,255,255,35);"
        "border:2px solid rgba(255,255,255,120);"
        "border-radius:14px;"
        "}"
        "QPushButton:hover{"
        "background:rgba(255,255,255,55);"
        "border:2px solid gold;"
        "}"
        );

    updateIcon();

    anim = new QPropertyAnimation(this,"geometry",this);
    anim->setDuration(180);

    connect(this,&QPushButton::clicked,[=](){
        emit clickedCard(this);
    });
}

int CardWidget::cardId() const
{
    return m_id;
}

bool CardWidget::isOpened() const
{
    return m_opened;
}

bool CardWidget::isMatched() const
{
    return m_matched;
}

void CardWidget::updateIcon()
{
    QString path;

    if(m_opened || m_matched)
    {
        path = QCoreApplication::applicationDirPath()
        + QString("/res/cards/%1.png").arg(m_id);
    }
    else
    {
        path = QCoreApplication::applicationDirPath()
        + "/res/cards/back.png";
    }

    setIcon(QIcon(path));
    setIconSize(size());
}

void CardWidget::flipOpen()
{
    if(m_opened || m_matched) return;

    m_opened=true;
    updateIcon();
}

void CardWidget::flipClose()
{
    if(m_matched) return;

    m_opened=false;
    updateIcon();
}

void CardWidget::setMatched()
{
    m_matched=true;
    m_opened=true;

    setStyleSheet(
        "border:2px solid gold;"
        "border-radius:10px;"
        );

    updateIcon();
}
