#include "animatedbutton.h"

#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QMouseEvent>

AnimatedButton::AnimatedButton(const QString& text,QWidget* parent)
    : QPushButton(text,parent)
{
    setCursor(Qt::PointingHandCursor);
    setFixedSize(280,75);

    setStyleSheet(
        "QPushButton{"
        "border:none;"
        "background:transparent;"
        "color:white;"
        "font-size:30px;"
        "font-weight:bold;"
        "}"
        );

    glow = new QGraphicsDropShadowEffect(this);
    glow->setOffset(0,0);
    glow->setBlurRadius(25);
    glow->setColor(QColor(255,255,255));

    setGraphicsEffect(glow);

    startBreath();
}

void AnimatedButton::startBreath()
{
    glowAnim = new QPropertyAnimation(glow,"blurRadius",this);
    glowAnim->setStartValue(18);
    glowAnim->setEndValue(35);
    glowAnim->setDuration(1200);
    glowAnim->setLoopCount(-1);
    glowAnim->setEasingCurve(QEasingCurve::InOutSine);
    glowAnim->start();
}

void AnimatedButton::enterEvent(QEnterEvent* event)
{
    setStyleSheet(
        "QPushButton{"
        "border:none;"
        "background:transparent;"
        "color:rgb(255,230,120);"
        "font-size:36px;"
        "font-weight:bold;"
        "}"
        );

    glow->setColor(QColor(255,230,120));

    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent* event)
{
    setStyleSheet(
        "QPushButton{"
        "border:none;"
        "background:transparent;"
        "color:white;"
        "font-size:30px;"
        "font-weight:bold;"
        "}"
        );

    glow->setColor(QColor(255,255,255));

    QPushButton::leaveEvent(event);
}

void AnimatedButton::mousePressEvent(QMouseEvent* event)
{
    move(x(),y()+3);
    QPushButton::mousePressEvent(event);
}

void AnimatedButton::mouseReleaseEvent(QMouseEvent* event)
{
    move(x(),y()-3);
    QPushButton::mouseReleaseEvent(event);
}
