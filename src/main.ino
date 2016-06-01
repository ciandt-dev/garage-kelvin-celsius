
#include <ESP8266WiFi.h>
#include <Timer.h>
#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char *ssid = "WiFiGaragem";
const char *password = "senhaGaragem";

ESP8266WebServer server(80);
Timer t;

float hum, temp;

void setup() {
  delay(200);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  webserver_setup();
  dht_setup();
  remote_setup();

  Serial.println("HTTP server started");
}

void loop() {
  t.update();
  server.handleClient();
}
