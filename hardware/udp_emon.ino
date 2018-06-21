#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUDP.h>
#include <EmonLib.h>
EnergyMonitor emon1;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //dimensian a char array to hold our data packet
String datReq; //String for our data
int packetSize;
unsigned int localPort = 2390;
WiFiUDP Udp;  
void setup() {
  Serial.begin(115200);
  emon1.current(1,56);
  WiFiManager wifiManager;
  IPAddress _ip = IPAddress(192, 168, 0, 102);
  IPAddress _gw = IPAddress(192, 168, 0, 1);
  IPAddress _sn = IPAddress(255, 255, 255, 0);
  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);
  
  if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("connected...yeey :)");
  Serial.println();
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  Udp.begin(localPort); 
}

void loop() {
packetSize = Udp.parsePacket();
if(packetSize>0) 
{
   Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); //Read the data request
    String datReq(packetBuffer); //Convert char array packetBuffer into a string called datReq
    
    if (datReq =="Temperature") { //Do the following if Temperature is requested
    
      float sensorValue = power(); //Read the temperature
      
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(sensorValue); //Send the temperature data
      Udp.endPacket(); //End the packet
     }
  }
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
}

float power(){
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  float power = Irms*220.0; 
  if(power<30)  Serial.print(0.0);
  else  Serial.print(Irms*220.0);         // Apparent power
  Serial.print(" ");
  Serial.println(Irms);
  return (Irms*220.0);
}

