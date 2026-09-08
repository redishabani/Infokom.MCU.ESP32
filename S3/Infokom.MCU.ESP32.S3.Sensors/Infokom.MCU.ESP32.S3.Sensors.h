#ifndef INFOKOM_S3_SENSORS_H
#define INFOKOM_S3_SENSORS_H

#include <Arduino.h>

class InfokomLightController {
private:
    int _ldrPin;
    int _buzzerPin;
    int _threshold;
    int _frequency;

public:
    InfokomLightController(int ldrPin, int buzzerPin, int threshold = 1500, int frequency = 2000);
    void begin();
    bool isDark();
    void triggerBeep(int durationMs = 50);
};

#endif
