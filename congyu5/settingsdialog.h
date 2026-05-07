#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>

class QSlider;
class QPushButton;
class QLabel;
class QCheckBox;
class QComboBox;

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
    QLabel* volumeLabel{};

    QCheckBox* soundCheck{};
    QComboBox* speedBox{};

    QPushButton* backBtn{};
};

#endif
