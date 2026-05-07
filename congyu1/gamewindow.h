#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVector>

class QGridLayout;
class QPushButton;
class CardWidget;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(int pairCount,QWidget *parent = nullptr);

signals:
    void backToHall();
    void gameWin();

private:
    void initCards(int pairCount);
    void onCardClicked(CardWidget* card);
    void checkWin();

private:
    QVector<CardWidget*> cards;

    CardWidget* firstCard{};
    CardWidget* secondCard{};

    bool busy=false;
    int matchedCount=0;

    QPushButton* backBtn{};
    QGridLayout* grid{};
};

#endif
