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

    layout->addSpacing(10);
    layout->addLayout(grid,1);
    layout->addSpacing(20);

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

    std::shuffle(ids.begin(),
                 ids.end(),
                 *QRandomGenerator::global());

    int cols;
    QSize cardSize;
    int spacing;

    // 简单模式
    if(pairCount==5)
    {
        cols = 5;
        cardSize = QSize(160,220);
        spacing = 28;
    }
    // 困难模式
    else
    {
        cols = 4;
        cardSize = QSize(115,160);
        spacing = 12;
    }

    grid->setSpacing(spacing);

    for(int i=0;i<ids.size();i++)
    {
        CardWidget* card =
            new CardWidget(ids[i],cardSize);

        cards.push_back(card);

        connect(card,
                &CardWidget::clickedCard,
                this,
                &GameWindow::onCardClicked);

        grid->addWidget(card,
                        i/cols,
                        i%cols,
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
    if(matchedCount != cards.size())
        return;

    QMessageBox msg(this);

    msg.setWindowTitle("胜利");
    msg.setText("🎉 恭喜通关！\n\n你完成了所有配对！");
    msg.setIcon(QMessageBox::NoIcon);

    QPushButton* restartBtn =
        msg.addButton("再来一局", QMessageBox::AcceptRole);

    QPushButton* backBtn =
        msg.addButton("返回大厅", QMessageBox::RejectRole);

    msg.setStyleSheet(
        "QMessageBox{"
        "background:rgb(25,35,60);"
        "color:white;"
        "font-size:22px;"
        "}"
        "QLabel{"
        "color:gold;"
        "font-size:28px;"
        "min-width:320px;"
        "}"
        "QPushButton{"
        "min-width:140px;"
        "height:45px;"
        "border:none;"
        "border-radius:10px;"
        "font-size:18px;"
        "color:white;"
        "background:rgb(60,120,220);"
        "padding:6px 12px;"
        "}"
        "QPushButton:hover{"
        "background:rgb(90,150,255);"
        "}"
        );

    msg.exec();

    if(msg.clickedButton() == restartBtn)
    {
        emit backToHall();
    }
    else if(msg.clickedButton() == backBtn)
    {
        emit gameWin();
    }
}
