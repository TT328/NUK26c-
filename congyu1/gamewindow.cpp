#include "gamewindow.h"
#include "cardwidget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>
#include <algorithm>

GameWindow::GameWindow(int pairCount,QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(
        "background:qlineargradient("
        "x1:0,y1:0,x2:1,y2:1,"
        "stop:0 rgb(25,35,60),"
        "stop:1 rgb(10,10,20));"
        );

    auto layout = new QVBoxLayout(this);

    backBtn = new QPushButton("返回");
    backBtn->setFixedSize(120,45);

    backBtn->setStyleSheet(
        "QPushButton{"
        "color:white;"
        "font-size:22px;"
        "background:rgba(255,255,255,40);"
        "border-radius:8px;"
        "}"
        "QPushButton:hover{"
        "background:rgba(255,255,255,80);"
        "}"
        );

    layout->addWidget(backBtn,0,Qt::AlignLeft);

    grid = new QGridLayout;
    grid->setSpacing(20);

    layout->addStretch();
    layout->addLayout(grid,1);
    layout->addStretch();

    initCards(pairCount);

    connect(backBtn,&QPushButton::clicked,[=](){
        emit backToHall();
    });
}

void GameWindow::initCards(int pairCount)
{
    QVector<int> ids;

    for(int i=1;i<=pairCount;i++)
    {
        ids.push_back(i);
        ids.push_back(i);
    }

    std::shuffle(ids.begin(),ids.end(),
                 *QRandomGenerator::global());

    int cols = (pairCount==5)?5:4;

    for(int i=0;i<ids.size();i++)
    {
        CardWidget* card = new CardWidget(ids[i]);

        cards.push_back(card);

        connect(card,&CardWidget::clickedCard,
                this,&GameWindow::onCardClicked);

        grid->addWidget(card,i/cols,i%cols,
                        Qt::AlignCenter);
    }
}

void GameWindow::onCardClicked(CardWidget *card)
{
    if(busy) return;
    if(card->isOpened()) return;
    if(card->isMatched()) return;

    card->flipOpen();

    if(!firstCard)
    {
        firstCard=card;
        return;
    }

    secondCard=card;
    busy=true;

    if(firstCard->cardId()==secondCard->cardId())
    {
        firstCard->setMatched();
        secondCard->setMatched();

        matchedCount+=2;

        firstCard=nullptr;
        secondCard=nullptr;
        busy=false;

        checkWin();
    }
    else
    {
        QTimer::singleShot(800,[=](){

            firstCard->flipClose();
            secondCard->flipClose();

            firstCard=nullptr;
            secondCard=nullptr;
            busy=false;
        });
    }
}

void GameWindow::checkWin()
{
    if(matchedCount==cards.size())
    {
        QMessageBox::information(this,
                                 "胜利",
                                 "恭喜通关！");
        emit gameWin();
    }
}
