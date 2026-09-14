#include "Infokom.MCU.ESP32.S3.Sensors.h"

InfokomLightController::InfokomLightController(int ldrPin, int buzzerPin, int threshold, int frequency) {
    _ldrPin = ldrPin;
    _buzzerPin = buzzerPin;
    _threshold = threshold;
    _frequency = frequency;
}

void InfokomLightController::begin() {
    analogSetAttenuation(ADC_11db);
    //ledcAttach(_buzzerPin, _frequency, 8); 
}

bool InfokomLightController::isDark() {
    return analogRead(_ldrPin) < _threshold;
}

void InfokomLightController::triggerBeep(int durationMs) {
    ledcWrite(_buzzerPin, 128); 
    delay(durationMs);
    ledcWrite(_buzzerPin, 0);   
}
