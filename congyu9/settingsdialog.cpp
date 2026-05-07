#include "settingsdialog.h"
#include "gamesettings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);

    setStyleSheet(
        "QWidget{"
        "background:rgba(255,255,255,110);"
        "border-radius:20px;"
        "color:rgb(50,35,20);"
        "font-size:22px;"
        "font-weight:600;"
        "}"
        "QSlider::groove:horizontal{"
        "height:10px;"
        "background:rgba(255,255,255,180);"
        "border-radius:5px;"
        "}"
        "QSlider::handle:horizontal{"
        "width:22px;"
        "background:rgb(255,210,120);"
        "border-radius:11px;"
        "margin:-6 0;"
        "}"
        "QCheckBox::indicator{"
        "width:22px;"
        "height:22px;"
        "}"
        "QComboBox{"
        "background:white;"
        "padding:8px;"
        "border-radius:10px;"
        "min-width:140px;"
        "}"
        );

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(28);
    layout->setContentsMargins(120,80,120,80);

    QLabel* title = new QLabel("游戏设置");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:34px;"
        "font-weight:800;"
        "color:rgb(70,45,20);"
        "background:transparent;"
        );

    // 音量
    QLabel* musicText = new QLabel("背景音乐");
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(GameSettings::musicVolume);

    volumeLabel =
        new QLabel(QString("%1%").arg(GameSettings::musicVolume));

    auto row1 = new QHBoxLayout;
    row1->addWidget(musicText);
    row1->addSpacing(20);
    row1->addWidget(volumeSlider,1);
    row1->addSpacing(20);
    row1->addWidget(volumeLabel);

    // 音效
    QLabel* soundText = new QLabel("游戏音效");
    soundCheck = new QCheckBox("开启");
    soundCheck->setChecked(GameSettings::soundEnabled);

    auto row2 = new QHBoxLayout;
    row2->addWidget(soundText);
    row2->addStretch();
    row2->addWidget(soundCheck);

    // 翻牌速度
    QLabel* speedText = new QLabel("翻牌速度");
    speedBox = new QComboBox;
    speedBox->addItem("慢");
    speedBox->addItem("中");
    speedBox->addItem("快");
    speedBox->setCurrentIndex(1);

    auto row3 = new QHBoxLayout;
    row3->addWidget(speedText);
    row3->addStretch();
    row3->addWidget(speedBox);

    backBtn = new QPushButton("返回");
    backBtn->setFixedSize(180,55);
    backBtn->setStyleSheet(
        "QPushButton{"
        "background:rgba(255,255,255,180);"
        "border:none;"
        "border-radius:14px;"
        "font-size:22px;"
        "color:rgb(50,35,20);"
        "}"
        "QPushButton:hover{"
        "background:white;"
        "}"
        );

    layout->addWidget(title);
    layout->addSpacing(30);
    layout->addLayout(row1);
    layout->addLayout(row2);
    layout->addLayout(row3);
    layout->addSpacing(40);
    layout->addWidget(backBtn,0,Qt::AlignCenter);

    connect(volumeSlider,&QSlider::valueChanged,
            this,[=](int value)
            {
                GameSettings::musicVolume=value;
                volumeLabel->setText(QString("%1%").arg(value));
                emit volumeChanged(value);
            });

    connect(soundCheck,&QCheckBox::toggled,
            this,[=](bool checked)
            {
                GameSettings::soundEnabled=checked;
            });

    connect(speedBox,
            &QComboBox::currentIndexChanged,
            this,
            [=](int index)
            {
                if(index == 0)
                    GameSettings::flipSpeed = 240;

                if(index == 1)
                    GameSettings::flipSpeed = 160;

                if(index == 2)
                    GameSettings::flipSpeed = 80;
            });

    connect(backBtn,&QPushButton::clicked,[=](){
        emit backClicked();
    });
}
