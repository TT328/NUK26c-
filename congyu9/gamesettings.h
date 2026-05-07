#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QString>

class GameSettings
{
public:
    static int musicVolume;
    static bool soundEnabled;
    static int flipSpeed;

    static void playSound(const QString& file);
};

#endif
