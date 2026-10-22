#include "leds.h"

void setLED(uint8_t r, uint8_t g, uint8_t b) {
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
    neopixelWrite(PIN_NEOPIXEL, r, g, b);
}

void showWorking() {
  setLED(0, 0, 255); // Blue
}

void showError() {
  setLED(255, 0, 0); // Red
}

void showSuccess() {
  setLED(0, 255, 0); // Green
}