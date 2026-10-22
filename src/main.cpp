#include "wifi_login.h"
#include "leds.h"

bool listenForString(String &out) {
    static String buffer;
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n') {
            out = buffer;
            out.trim();
            buffer = "";
            return true;
        }
        buffer += c;
    }
    return false;
}

const uint16_t LISTEN_PORT = 5000;
WiFiServer server(LISTEN_PORT);

// Non-blocking: call every loop(). Accepts a TCP client and returns true with
// the received line in `out` once a full line (ending in '\n') has arrived.
bool listenForWiFiString(String &out) {
    static WiFiClient client;
    static String buffer;

    // Only look for a new client once the old one is gone AND fully read.
    // (A client that sends and closes quickly can still have unread data.)
    if (!client.connected() && !client.available()) {
        WiFiClient next = server.accept();  // empty client if nobody is connecting
        if (next.connected() || next.available()) {
            client = next;
            buffer = "";
            Serial.println("Client connected");
        }
    }
    while (client.available()) {
        char c = client.read();
        if (c == '\n') {
            client.println("OK");  // lets the sender confirm delivery
            out = buffer;
            out.trim();
            buffer = "";
            return true;
        }
        buffer += c;
    }
    return false;
}

void setup() {
  Serial.begin(115200);
    if (!connectToWiFi()) {
        showError(); // Red
    } else {
        showSuccess(); // Green
        server.begin();
        Serial.printf("Listening on %s:%u\n", WiFi.localIP().toString().c_str(), LISTEN_PORT);
    }
}

void loop() {
    String message;
    if (listenForWiFiString(message)) {
        Serial.print("Received: ");
        Serial.println(message);
    }
}