#define _DISABLE_TLS_
#define _DEBUG_
#define THINGER_SERVER "serverIP" //Enter your thinger server ip address

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerWifi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#define USERNAME "username" //Enter username
#define DEVICE_ID "deviceID"  //Enter device ID
#define DEVICE_CREDENTIAL "deviceCredential"  //Enter device credentials


ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Smart-Plug");  //AP name
  Serial.println("connected...yeey! :)");

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)

  //Device 1
  thing["led1"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(D1);
    }
    else {
      digitalWrite(D1, in ? HIGH : LOW);
    }
  };
  //Device 2
  thing["led2"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(D2);
    }
    else {
      digitalWrite(D2, in ? HIGH : LOW);
    }
  };
  //Device 3
  thing["led3"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(D3);
    }
    else {
      digitalWrite(D3, in ? HIGH : LOW);
    }
  };
  //Device 4
  thing["led4"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(D4);
    }
    else {
      digitalWrite(D4, in ? HIGH : LOW);
    }
  };

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
  
}

