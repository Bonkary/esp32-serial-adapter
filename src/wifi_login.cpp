#include "wifi_login.h"

WiFiServer server(LISTEN_PORT);

bool connectToWiFi() {
    showWorking(); // Blue
    int timeout = 10;
    WiFi.begin(Login::WIFI_SSID, Login::WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        timeout -= 1;
        if (timeout <= 0) {
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connected! IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    Serial.println("WiFi connection failed");
    return false;
}