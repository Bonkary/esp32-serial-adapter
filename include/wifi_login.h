#ifndef WIFI_LOGIN_H
#define WIFI_LOGIN_H

#include <WiFi.h>
#include "credentials.h"
#include "leds.h"

constexpr uint16_t LISTEN_PORT = 5000;
extern WiFiServer server;  // defined once in wifi_login.cpp

bool connectToWiFi();

#endif // WIFI_LOGIN_H