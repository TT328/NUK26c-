#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QPushButton>

class QPropertyAnimation;

class CardWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit CardWidget(int id,QWidget* parent=nullptr);

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

private:
    int m_id{};
    bool m_opened=false;
    bool m_matched=false;

    QPropertyAnimation* anim{};
};

#endif
