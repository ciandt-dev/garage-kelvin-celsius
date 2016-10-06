
#include <ESP8266WiFi.h>
#include <Timer.h>
#include <WiFiClient.h>     //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


const char *ssid = "WiFiGaragem";
const char *password = "senhaGaragem";

ESP8266WebServer server(80);
Timer t;

long voteStartTime = 0;


float hum, temp;

void setup() {
Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");


WiFiManager wifiManager;
//wifiManager.resetSettings();
wifiManager.autoConnect("ArCondicionado");
Serial.println("connected...yeey :)");
webserver_setup();

dht_setup();
remote_setup();
}

void loop() {
  t.update();
  server.handleClient();
}
