#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPushButton>

class QPropertyAnimation;
class QGraphicsDropShadowEffect;

class AnimatedButton : public QPushButton
{
    Q_OBJECT

public:
    explicit AnimatedButton(
        const QString& text,
        bool small = false,
        QWidget* parent = nullptr
        );

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void startBreath();

private:
    QGraphicsDropShadowEffect* glow{};
    QPropertyAnimation* glowAnim{};
    bool m_small=false;
};

#endif
