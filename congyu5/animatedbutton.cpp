#include "animatedbutton.h"

#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QEasingCurve>

AnimatedButton::AnimatedButton(
    const QString& text,
    bool small,
    QWidget* parent
    )
    : QPushButton(text,parent),
    m_small(small)
{
    setCursor(Qt::PointingHandCursor);

    if(m_small)
        setFixedSize(170,55);
    else
        setFixedSize(320,82);

    int radius = m_small ? 16 : 22;
    int fontSize = m_small ? 22 : 30;

    setStyleSheet(QString(
                      "QPushButton{"
                      "border:none;"
                      "border-radius:%1px;"
                      "background:rgba(255,255,255,150);"
                      "color:rgb(55,40,30);"
                      "font-size:%2px;"
                      "font-weight:700;"
                      "padding:8px;"
                      "}"
                      ).arg(radius).arg(fontSize));

    glow = new QGraphicsDropShadowEffect(this);
    glow->setOffset(0,4);
    glow->setBlurRadius(28);
    glow->setColor(QColor(255,255,255,120));

    setGraphicsEffect(glow);

    startBreath();
}

void AnimatedButton::startBreath()
{
    glowAnim = new QPropertyAnimation(glow,"blurRadius",this);
    glowAnim->setStartValue(20);
    glowAnim->setEndValue(36);
    glowAnim->setDuration(1500);
    glowAnim->setLoopCount(-1);
    glowAnim->setEasingCurve(QEasingCurve::InOutSine);
    glowAnim->start();
}

void AnimatedButton::enterEvent(QEnterEvent* event)
{
    int radius = m_small ? 16 : 22;
    int fontSize = m_small ? 25 : 34;

    setStyleSheet(QString(
                      "QPushButton{"
                      "border:none;"
                      "border-radius:%1px;"
                      "background:rgba(255,255,255,210);"
                      "color:rgb(35,20,10);"
                      "font-size:%2px;"
                      "font-weight:800;"
                      "padding:8px;"
                      "}"
                      ).arg(radius).arg(fontSize));

    glow->setBlurRadius(45);
    glow->setColor(QColor(255,245,180));

    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent* event)
{
    int radius = m_small ? 16 : 22;
    int fontSize = m_small ? 22 : 30;

    setStyleSheet(QString(
                      "QPushButton{"
                      "border:none;"
                      "border-radius:%1px;"
                      "background:rgba(255,255,255,150);"
                      "color:rgb(55,40,30);"
                      "font-size:%2px;"
                      "font-weight:700;"
                      "padding:8px;"
                      "}"
                      ).arg(radius).arg(fontSize));

    glow->setBlurRadius(28);
    glow->setColor(QColor(255,255,255,120));

    QPushButton::leaveEvent(event);
}

void AnimatedButton::mousePressEvent(QMouseEvent* event)
{
    move(x(),y()+2);
    QPushButton::mousePressEvent(event);
}

void AnimatedButton::mouseReleaseEvent(QMouseEvent* event)
{
    move(x(),y()-2);
    QPushButton::mouseReleaseEvent(event);
}
