// Task: Read WiFi module and connect it.
//
// arduino_secrets.h file contents:
#define SECRET_SSID "YourNetworkName"
#define SECRET_PASS "YourNetworkPassword"
// --------------------------------

#include <WiFiNINA.h>
#include "arduino_secrets.h"

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(SECRET_SSID);

    WiFi.begin(SECRET_SSID, SECRET_PASS);

    if (WiFi.status() != WL_CONNECTED) {
      delay(5000);
    }
  }

  Serial.println("Connected!");

  Serial.print("Arduino IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
    Serial.begin(9600);

    while (!Serial) {};

    if (WiFi.status() == WL_NO_MODULE){
        Serial.println("Wi-Fi module unavailable.");
        while (true) {}
    }

    connectWiFi();
}

void loop(){
    if (WiFi.status() != WL_CONNECTED ){
        Serial.println("Connection lost. Reconnecting...");
        connectWiFi();
    }
}
