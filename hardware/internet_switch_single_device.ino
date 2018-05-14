#define _DISABLE_TLS_
#define _DEBUG_
#define THINGER_SERVER "139.59.41.62"

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerWifi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define USERNAME "admin"
#define DEVICE_ID "multi_test"
#define DEVICE_CREDENTIAL "abc@123"


ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("SIH-project-switch");
  Serial.println("connected...yeey :)");

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)

  thing["led"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(D1);
    }
    else {
      digitalWrite(D1, in ? HIGH : LOW);
    }
  }

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
  
}

void loop() {
  thing.handle();
}
