#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>

class QPropertyAnimation;

class CardWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit CardWidget(
        int id,
        QSize cardSize = QSize(120,160),
        QWidget* parent=nullptr
        );

    int cardId() const;
    bool isOpened() const;
    bool isMatched() const;

    void flipOpen();
    void flipClose();
    void setMatched();

signals:
    void clickedCard(CardWidget* card);

private:
    void updateIcon();
    void playFlipAnimation(bool open);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int m_id{};
    QSize m_size;

    bool m_opened=false;
    bool m_matched=false;

    QGraphicsDropShadowEffect* glow{};
};

#endif
