
#ifndef AUDIO_COMPASS_H
#define AUDIO_COMPASS_H

#include <Arduino.h>

class AudioCompass {
public:
    static void begin();
    static String getDirection();
};

#endif
