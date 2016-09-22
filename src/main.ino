
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
  delay(5000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  // WiFi.softAP(ssid, password);
  //
  // IPAddress myIP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(myIP);

  //webserver_setup();

  WiFiManager wifiManager;
  wifiManager.setDebugOutput(true);
  wifiManager.setTimeout(10);

  // wifiManager.setSTAStaticIPConfig(IPAddress(192,168,4,10), IPAddress(192,168,4,1), IPAddress(255,255,255,0));

  if(!wifiManager.startConfigPortal("nomeA")){
    Serial.println("fail to connect");
    delay(3000);
    ESP.reset();
    delay(5000);
  } else {
    delay(5000);
    Serial.println("aew");
    Serial.println("IP do WiFi:");
    Serial.println(WiFi.localIP());
  }

  //dht_setup();
  //remote_setup();
  // wifiManager.autoConnect("nomeB");
  Serial.println("HTTP server started");
}

void loop() {
  //t.update();
  //server.handleClient();
}
