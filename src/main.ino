
#include <ESP8266WiFi.h>
#include <Timer.h>
#include <WiFiClient.h>     //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define IDLE 0
#define VOTING 1
#define SET_TEMP 2

#define VOTING_TIME 30000
#define SET_TEMP_TIME 5000

int state = 0;
long nextStateTimer = 0;

const char *ssid = "WiFiGaragem";
const char *password = "senhaGaragem";

ESP8266WebServer server(80);
Timer t;

class IpWithVote {
  public:
    int vote;
    String ip;
};

IpWithVote allVotes[10];
int numberOfVotes = 0;
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
  if(state = VOTING && nextStateTimer > millis() ) {
    toSetTemp();
  } else if (state = VOTING && nextStateTimer > millis() ) {
    toIdle();
  }
}
void toSetTemp(){
  state = SET_TEMP;
  nextStateTimer = millis() + SET_TEMP_TIME;
}
void toIdle(){
  numberOfVotes = 0;
  //Logica para mandar o comando
  int voteSum[5] = {0,0,0,0,0};
  for (int i = 0; i < numberOfVotes; i++) {
    voteSum[allVotes[i].vote + 2]++;
  }
  int maxVal = 0, voteMaxVal = 0;

  for (int i = 0; i < 5; i++) {
    if(voteSum[i] > maxVal){
      maxVal = voteSum[i];
      voteMaxVal = i -2;
    }
  }
  Serial.print("Win:");
  Serial.println(voteMaxVal);
  state = IDLE;
}

void startVoting() {
  state = VOTING;
  nextStateTimer = millis() + VOTING_TIME;
}
