#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include "animatedbutton.h"
#include "settingsdialog.h"
#include "gamewindow.h"

class QWidget;
class QStackedWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void initWindow();
    void initUi();
    void initBackground();
    void initMusic();
    void initConnections();

private:
    QWidget* central{};
    QStackedWidget* stack{};

    QWidget* hallPage{};
    QWidget* modePage{};
    SettingsDialog* settingPage{};

    GameWindow* easyGame{};
    GameWindow* hardGame{};

    QLabel* bgLabel{};

    QMediaPlayer* musicPlayer{};
    QAudioOutput* musicAudio{};

    AnimatedButton* startBtn{};
    AnimatedButton* settingBtn{};
    AnimatedButton* quitBtn{};

    QPushButton* easyBtn{};
    QPushButton* hardBtn{};
    QPushButton* backBtn{};
};

#endif
