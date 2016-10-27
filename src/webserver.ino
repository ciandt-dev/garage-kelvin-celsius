

#include <ESP8266WebServer.h>
#include <FS.h>

/**

POST /api/vote/
-2

*/

class IpWithVote {
  public:
    int vote;
    String ip;
};

IpWithVote allVotes[10];
int numberOfVotes = 0;

void handleVote() {
  IpWithVote *newVote;
  server.send(200, "application/json","OK");
  Serial.print("Voto: ");
  Serial.println(server.arg("plain"));
  // TODO descobrir como extrair o voto
  //Serial.println(server.);
  Serial.println(server.client().remoteIP().toString());

  newVote = new IpWithVote();
  newVote->vote = 1;
  newVote->ip = server.client().remoteIP().toString();

  allVotes[numberOfVotes] = *newVote;
  Serial.println(allVotes[numberOfVotes].ip + ' ' + allVotes[numberOfVotes].vote);
  numberOfVotes++;
}

/**
{ temp": "24.20", "hum": "42.90", "status": "voting", "votes": "[0,1,2,-2,-1,-1]", "timeRemaining": "300" }
*/

void handleStatus() {
  server.send(200, "application/json",
  "{ \"temp\": \""+ String(temp) +
  "\", \"hum\": \""+ String(hum) +
  "\", \"status\": \""+ 0 +
  "\", \"votes\": "+ "[0,1,2,-2,-1,-1]" +
  ", \"timeRemaining\": \""+ String(300)
  +"\" }");
}

void handleControl() {

  String message = "";
  if(server.hasArg("plain")){
    remote_sendCommand(server.arg("plain").toInt(), 2);
  }
	server.send ( 200, "text/plain", "OK" );
}

void webserver_setup(){
  SPIFFS.begin();
  server.on("/api/status", handleStatus);
  server.on("/api/vote", handleVote);
  server.on("/api/control", handleControl);
  server.onNotFound([](){
  if(!webserver_handleFileRead(server.uri()))
    server.send(404, "text/plain", "FileNotFound");
  });
  server.begin();
}

String webserver_getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}


bool webserver_handleFileRead(String path){

  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";
  String contentType = webserver_getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
