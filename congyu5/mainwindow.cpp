#include "mainwindow.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QUrl>
#include <QApplication>
#include <QCoreApplication>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWindow();
    initUi();
    initBackground();
    initMusic();
    initConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWindow()
{
    resize(1280, 720);
    setMinimumSize(900, 600);
    setWindowTitle("翻牌游戏");
}

void MainWindow::initUi()
{
    central = new QWidget(this);
    setCentralWidget(central);

    // ===== 背景图 =====
    bgLabel = new QLabel(central);
    bgLabel->setGeometry(rect());
    bgLabel->setScaledContents(true);

    // ===== UI层 =====
    stack = new QStackedWidget(central);
    stack->setGeometry(rect());
    stack->raise();
    stack->setStyleSheet("background:transparent;");

    //--------------------------------
    // 大厅页
    //--------------------------------
    hallPage = new QWidget;
    hallPage->setStyleSheet("background:transparent;");

    auto hallLayout = new QVBoxLayout(hallPage);
    hallLayout->addStretch();

    startBtn = new AnimatedButton("开始游戏");
    settingBtn = new AnimatedButton("游戏设置");
    quitBtn = new AnimatedButton("退出游戏");

    QList<QPushButton*> buttons = {
        startBtn, settingBtn, quitBtn
    };

    for(auto btn : buttons)
    {
        hallLayout->addWidget(btn, 0, Qt::AlignHCenter);
        hallLayout->addSpacing(25);
    }

    hallLayout->addStretch();

    //--------------------------------
    // 模式页
    //--------------------------------
    modePage = new QWidget;
    modePage->setStyleSheet("background:transparent;");

    auto modeLayout = new QVBoxLayout(modePage);
    modeLayout->addStretch();

    easyBtn = new AnimatedButton("简单模式");
    hardBtn = new AnimatedButton("困难模式");
    backBtn = new AnimatedButton("返回");

    QList<QPushButton*> modeBtns = {
        easyBtn, hardBtn, backBtn
    };

    for(auto btn : modeBtns)
    {
        btn->setFixedSize(320,82);

        modeLayout->addWidget(btn,0,Qt::AlignHCenter);
        modeLayout->addSpacing(24);
    }

    modeLayout->addStretch();

    //--------------------------------
    // 设置页 / 游戏页
    //--------------------------------
    settingPage = new SettingsDialog;
    easyGame = new GameWindow(5);
    hardGame = new GameWindow(8);

    //--------------------------------
    // 加入 stack
    //--------------------------------
    stack->addWidget(hallPage);
    stack->addWidget(modePage);
    stack->addWidget(settingPage);
    stack->addWidget(easyGame);
    stack->addWidget(hardGame);
}

void MainWindow::initBackground()
{
    QString root = QCoreApplication::applicationDirPath();

    QPixmap pix(root + "/res/bg.png");

    if(!pix.isNull())
    {
        bgLabel->setPixmap(pix);
    }
}

void MainWindow::initMusic()
{
    musicPlayer = new QMediaPlayer(this);
    musicAudio = new QAudioOutput(this);

    musicPlayer->setAudioOutput(musicAudio);
    musicAudio->setVolume(0.5);

    QString root = QCoreApplication::applicationDirPath();

    musicPlayer->setSource(
        QUrl::fromLocalFile(root + "/res/music.mp3")
        );

    musicPlayer->play();

    connect(musicPlayer, &QMediaPlayer::mediaStatusChanged,
            this,
            [=](QMediaPlayer::MediaStatus status)
            {
                if(status == QMediaPlayer::EndOfMedia)
                {
                    musicPlayer->setPosition(0);
                    musicPlayer->play();
                }
            });
}

void MainWindow::initConnections()
{
    // 开始游戏
    connect(startBtn, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(modePage);
    });

    // 模式选择
    connect(easyBtn, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(easyGame);
    });

    connect(hardBtn, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(hardGame);
    });

    // 模式页返回
    connect(backBtn, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(hallPage);
    });

    // 设置页进入
    connect(settingBtn, &QPushButton::clicked, [=](){
        stack->setCurrentWidget(settingPage);
    });

    // 设置页返回
    connect(settingPage, &SettingsDialog::backClicked, [=](){
        stack->setCurrentWidget(hallPage);
    });

    // 音量
    connect(settingPage, &SettingsDialog::volumeChanged,
            this,
            [=](int value)
            {
                if(musicAudio)
                    musicAudio->setVolume(value / 100.0);
            });

    // 简单模式返回
    connect(easyGame, &GameWindow::backToHall, [=](){
        stack->setCurrentWidget(hallPage);
    });

    // 困难模式返回
    connect(hardGame, &GameWindow::backToHall, [=](){
        stack->setCurrentWidget(hallPage);
    });

    // 通关返回大厅
    connect(easyGame, &GameWindow::gameWin, [=](){
        stack->setCurrentWidget(hallPage);
    });

    connect(hardGame, &GameWindow::gameWin, [=](){
        stack->setCurrentWidget(hallPage);
    });

    // 退出
    connect(quitBtn, &QPushButton::clicked, [=](){
        qApp->quit();
    });
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if(bgLabel)
        bgLabel->setGeometry(central->rect());

    if(stack)
    {
        stack->setGeometry(central->rect());
        stack->raise();
    }
}
