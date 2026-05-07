#include "matchlabel.h"

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

MatchLabel::MatchLabel(QWidget *parent)
    : QLabel(parent)
{
    setText("✨ MATCH ✨");

    setStyleSheet(
        "color:rgb(255,230,120);"
        "font-size:42px;"
        "font-weight:900;"
        "background:transparent;"
        );

    adjustSize();

    auto opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(1.0);

    setGraphicsEffect(opacity);

    // 上浮动画
    auto moveAnim =
        new QPropertyAnimation(this,"pos");

    moveAnim->setDuration(900);

    QPoint start = pos();
    QPoint end = QPoint(start.x(),start.y()-80);

    moveAnim->setStartValue(start);
    moveAnim->setEndValue(end);

    // 渐隐动画
    auto fadeAnim =
        new QPropertyAnimation(opacity,"opacity");

    fadeAnim->setDuration(900);
    fadeAnim->setStartValue(1.0);
    fadeAnim->setEndValue(0.0);

    moveAnim->start(QAbstractAnimation::DeleteWhenStopped);
    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);

    connect(fadeAnim,
            &QPropertyAnimation::finished,
            this,
            &QWidget::deleteLater);
}

void MatchLabel::play()
{
    show();
}
