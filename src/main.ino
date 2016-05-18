
#include <ESP8266WiFi.h>
#include <Timer.h>
#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char *ssid = "WiFiGaragem";
const char *password = "senhaGaragem";

ESP8266WebServer server(80);
Timer t;

float hum, temp;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}


void handleSensor() {
  server.send(200, "application/json", "{ temp: "+ String(temp) +", hum: "+ String(hum) +" }");
}
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
  server.on("/", handleRoot);

  server.on("/api/sensor", handleSensor);
  server.on("/api/control", handleRoot);

  dht_setup();

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  t.update();
  server.handleClient();
}