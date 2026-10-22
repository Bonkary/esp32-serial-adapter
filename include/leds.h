#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

void setLED(uint8_t r, uint8_t g, uint8_t b);
void showWorking();
void showError();
void showSuccess();


#endif // LEDS_H