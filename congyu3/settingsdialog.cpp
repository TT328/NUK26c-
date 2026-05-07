#include "settingsdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    setStyleSheet(
        "QWidget{"
        "background:rgba(20,20,30,180);"
        "color:white;"
        "}"
        );

    auto layout = new QVBoxLayout(this);
    layout->addStretch();

    QLabel* title = new QLabel("音乐音量");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        );

    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    volumeSlider->setFixedWidth(400);

    backBtn = new QPushButton("返回");
    backBtn->setFixedSize(180,55);
    backBtn->setStyleSheet(
        "QPushButton{"
        "background:rgba(255,255,255,40);"
        "border-radius:10px;"
        "color:white;"
        "font-size:22px;"
        "}"
        "QPushButton:hover{"
        "background:rgba(255,255,255,80);"
        "}"
        );

    layout->addWidget(title,0,Qt::AlignCenter);
    layout->addSpacing(30);
    layout->addWidget(volumeSlider,0,Qt::AlignCenter);
    layout->addSpacing(50);
    layout->addWidget(backBtn,0,Qt::AlignCenter);
    layout->addStretch();

    connect(volumeSlider,&QSlider::valueChanged,
            this,&SettingsDialog::volumeChanged);

    connect(backBtn,&QPushButton::clicked,[=](){
        emit backClicked();
    });
}
