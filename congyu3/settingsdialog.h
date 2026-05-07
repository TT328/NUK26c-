#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>

class QSlider;
class QPushButton;

class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

signals:
    void volumeChanged(int value);
    void backClicked();

private:
    QSlider* volumeSlider{};
    QPushButton* backBtn{};
};

#endif
