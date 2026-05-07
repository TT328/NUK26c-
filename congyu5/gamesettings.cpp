#include "gamesettings.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCoreApplication>

int GameSettings::musicVolume = 50;
bool GameSettings::soundEnabled = true;
int GameSettings::flipSpeed = 180;

void GameSettings::playSound(const QString& file)
{
    if(!soundEnabled)
        return;

    auto player = new QMediaPlayer;
    auto audio = new QAudioOutput;

    player->setAudioOutput(audio);
    audio->setVolume(0.8);

    QString root =
        QCoreApplication::applicationDirPath();

    player->setSource(
        QUrl::fromLocalFile(
            root + "/res/sfx/" + file
            )
        );

    player->play();

    QObject::connect(
        player,
        &QMediaPlayer::mediaStatusChanged,
        [=](QMediaPlayer::MediaStatus status)
        {
            if(status==QMediaPlayer::EndOfMedia)
            {
                delete player;
                delete audio;
            }
        });
}
