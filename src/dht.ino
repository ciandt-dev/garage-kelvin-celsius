// Aqui fica o codigo da medição de temperatura
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE, 15);



void dht_setup() { t.every(5000, dht_update); }

void dht_update() {

  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (!isnan(temp)) {
    Serial.println("Temperatura lida ");
    Serial.print(temp);
    Serial.print(" -  ");
    Serial.println(hum);
  } else {
    Serial.println("Erro ao ler sensor");
  }
}
