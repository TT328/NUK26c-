#include "cardwidget.h"

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QIcon>
#include <QCoreApplication>
#include <QGraphicsDropShadowEffect>
#include <QEnterEvent>
#include <QTimer>
#include <QParallelAnimationGroup>
#include "gamesettings.h"

CardWidget::CardWidget(
    int id,
    QSize cardSize,
    QWidget* parent
    )
    : QPushButton(parent),
    m_id(id),
    m_size(cardSize)
{
    setFixedSize(m_size);
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

    // 阴影
    glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(35);
    glow->setOffset(0,10);
    glow->setColor(QColor(0,0,0,140));

    setGraphicsEffect(glow);

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

void CardWidget::playFlipAnimation(bool open)
{
    QRect oldRect = geometry();

    int cx = oldRect.center().x();
    int y  = oldRect.y();
    int h  = oldRect.height();

    QRect thinRect(cx - 5, y, 10, h);

    auto shrink = new QPropertyAnimation(this,"geometry");
    shrink->setDuration(GameSettings::flipSpeed / 2);

    shrink->setStartValue(oldRect);
    shrink->setEndValue(thinRect);

    auto expand = new QPropertyAnimation(this,"geometry");
    expand->setDuration(GameSettings::flipSpeed / 2);

    expand->setStartValue(thinRect);
    expand->setEndValue(oldRect);

    auto group = new QSequentialAnimationGroup(this);

    group->addAnimation(shrink);
    group->addAnimation(expand);

    connect(shrink,
            &QPropertyAnimation::finished,
            this,
            [=]()
            {
                m_opened = open;
                updateIcon();
            });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void CardWidget::flipOpen()
{
    if(m_opened || m_matched)
        return;

    GameSettings::playSound("flip.wav");

    playFlipAnimation(true);
}

void CardWidget::flipClose()
{
    if(m_matched)
        return;

    playFlipAnimation(false);
}

void CardWidget::setMatched()
{
    m_matched = true;
    m_opened = true;

    glow->setBlurRadius(55);
    glow->setOffset(0,0);
    glow->setColor(QColor(255,215,0,230));

    setStyleSheet(
        "QPushButton{"
        "border:2px solid gold;"
        "border-radius:14px;"
        "background:rgba(255,215,0,45);"
        "}"
        );

    updateIcon();
}

void CardWidget::playMatchAnimation()
{
    QRect oldRect = geometry();

    QRect bigRect(
        oldRect.x()-10,
        oldRect.y()-10,
        oldRect.width()+20,
        oldRect.height()+20
        );

    auto grow = new QPropertyAnimation(this,"geometry");
    grow->setDuration(140);
    grow->setStartValue(oldRect);
    grow->setEndValue(bigRect);
    grow->setEasingCurve(QEasingCurve::OutBack);

    auto back = new QPropertyAnimation(this,"geometry");
    back->setDuration(120);
    back->setStartValue(bigRect);
    back->setEndValue(oldRect);

    auto glowAnim =
        new QPropertyAnimation(glow,"blurRadius");

    glowAnim->setDuration(260);
    glowAnim->setStartValue(40);
    glowAnim->setEndValue(75);

    auto group = new QParallelAnimationGroup(this);

    auto seq = new QSequentialAnimationGroup;
    seq->addAnimation(grow);
    seq->addAnimation(back);

    group->addAnimation(seq);
    group->addAnimation(glowAnim);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void CardWidget::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);

    if(m_opened || m_matched)
        return;


    setStyleSheet(
        "QPushButton{"
        "background:rgba(255,255,255,70);"
        "border:2px solid rgb(255,215,0);"
        "border-radius:14px;"
        "}"
        );
}

void CardWidget::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);

    if(m_opened || m_matched)
        return;


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
}
