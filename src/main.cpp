#include "wifi_login.h"
#include "leds.h"

const int RX_PIN = 16;
const int TX_PIN = 5;

void sendConsoleCommand(const String &command) {
    Serial1.print(command);
    Serial1.print("\r\n");
}

bool listenForCommand(String &out) {
    static WiFiClient client;
    static String buffer;

    // Accept a new client if the current one is disconnected and has no available data.
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
    Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
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
    if (listenForCommand(message)) {
        sendConsoleCommand(message);
    }
}