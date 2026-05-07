#include "gamewindow.h"
#include "cardwidget.h"
#include "animatedbutton.h"
#include "gamesettings.h"
#include "matchlabel.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>
#include <algorithm>

GameWindow::GameWindow(int pairCount,QWidget *parent)
    : QWidget(parent),
    m_pairCount(pairCount)
{
    setStyleSheet(
        "background:qlineargradient("
        "x1:0,y1:0,x2:1,y2:1,"
        "stop:0 rgb(25,35,60),"
        "stop:1 rgb(10,10,20));"
        );

    auto layout = new QVBoxLayout(this);

    backBtn = new AnimatedButton("返回",true);
    layout->addWidget(backBtn,0,Qt::AlignLeft);

    grid = new QGridLayout;
    grid->setSpacing(20);

    layout->addSpacing(10);
    layout->addLayout(grid,1);
    layout->addSpacing(20);

    initCards(m_pairCount);

    connect(backBtn,&QPushButton::clicked,[=](){
        emit backToHall();
    });
}

void GameWindow::resetGame()
{
    firstCard=nullptr;
    secondCard=nullptr;
    busy=false;
    matchedCount=0;

    for(auto card:cards)
    {
        grid->removeWidget(card);
        delete card;
    }

    cards.clear();

    initCards(m_pairCount);
}

void GameWindow::initCards(int pairCount)
{
    QVector<int> ids;

    for(int i=1;i<=pairCount;i++)
    {
        ids.push_back(i);
        ids.push_back(i);
    }

    std::shuffle(
        ids.begin(),
        ids.end(),
        *QRandomGenerator::global()
        );

    int cols;
    QSize cardSize;
    int spacing;

    if(pairCount==5)
    {
        cols=5;
        cardSize=QSize(160,220);
        spacing=28;
    }
    else
    {
        cols=4;
        cardSize=QSize(115,160);
        spacing=12;
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

        grid->addWidget(
            card,
            i/cols,
            i%cols,
            Qt::AlignCenter
            );
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
        firstCard = card;
        return;
    }

    secondCard = card;
    busy = true;

    if(firstCard->cardId() == secondCard->cardId())
    {
        GameSettings::playSound("match.wav");

        firstCard->setMatched();
        secondCard->setMatched();

        firstCard->playMatchAnimation();
        secondCard->playMatchAnimation();

        MatchLabel* label = new MatchLabel(this);

        label->move(
            width()/2 - 120,
            height()/2 - 60
            );

        label->play();

        matchedCount += 2;

        firstCard = nullptr;
        secondCard = nullptr;
        busy = false;

        checkWin();
    }
    else
    {
        QTimer::singleShot(800,[=](){

            firstCard->flipClose();
            secondCard->flipClose();

            firstCard = nullptr;
            secondCard = nullptr;
            busy = false;
        });
    }
}

void GameWindow::checkWin()
{
    if(matchedCount != cards.size())
        return;

    GameSettings::playSound("win.wav");

    QMessageBox msg(this);

    msg.setWindowTitle("Victory");
    msg.setIcon(QMessageBox::NoIcon);

    msg.setText(
        "🏆 VICTORY 🏆\n\n"
        "恭喜完成全部配对！\n\n"
        "⭐ ⭐ ⭐ ⭐ ⭐"
        );

    QPushButton* restartBtn =
        msg.addButton("再来一局", QMessageBox::AcceptRole);

    QPushButton* hallBtn =
        msg.addButton("返回大厅", QMessageBox::RejectRole);

    msg.setStyleSheet(
        "QMessageBox{"
        "background:rgba(28,35,55,245);"
        "border:2px solid rgba(255,215,0,160);"
        "}"
        "QLabel{"
        "color:white;"
        "font-size:28px;"
        "font-weight:700;"
        "min-width:420px;"
        "padding:25px;"
        "qproperty-alignment: AlignCenter;"
        "}"
        "QPushButton{"
        "min-width:170px;"
        "height:55px;"
        "border:none;"
        "border-radius:16px;"
        "font-size:20px;"
        "font-weight:700;"
        "color:rgb(60,35,10);"
        "background:rgb(255,230,150);"
        "padding:8px;"
        "}"
        "QPushButton:hover{"
        "background:rgb(255,245,190);"
        "font-size:22px;"
        "}"
        );

    msg.exec();

    if(msg.clickedButton() == restartBtn)
        resetGame();
    else
        emit gameWin();
}
