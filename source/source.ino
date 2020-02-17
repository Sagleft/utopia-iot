#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

using std::string;

ESP8266WiFiMulti WiFiMulti;

#include "params.h"
#include "indicator.h"
#include "network.h"

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    digitalWrite(D7, HIGH);
    delay(500);
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    digitalWrite(D7, LOW);
    delay(500);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop() {
  resetIndicator();
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    if(checkClientConnection()) {
      indicateAlert();
    } else {
      indicateErr();
    }
  }

  delay(60000);
}
