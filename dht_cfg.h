#ifndef DHT_CFG
#define DHT_CFG
#include "config.h"

#define DHTPIN 4
#define DHTTYPE DHT11   

char tempString_2[20];


DHT dht(DHTPIN, DHTTYPE);
bool DHT_Running = false;


bool dht_start(){
  dht.begin();
  delay(WaitToPrintDelay);

  if (isnan(dht.readHumidity()) || isnan(dht.readTemperature())) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return false;
  }else{Serial.println("DHT sensor Connected Sucessfully");}
  DHT_Running = true;
  return true;
}

char* dht_run(){
  char tempString[20];

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  char temp[10];
  char hum[10];
  delay(WaitToPrintDelay);
  /*
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  */
  dtostrf(h, 2, 2, hum);
  dtostrf(t, 2, 2, temp);
  char buffer[2] = ";";
  strcat(tempString, hum);
  strcat(tempString, buffer);
  strcat(tempString, temp);
  strncpy ( tempString_2, tempString, sizeof(tempString_2) );
  return tempString_2;
}

void dht_error(){
  Serial.println("ERROR - DHT not working");
  delay(2000);
  Serial.end();
}
#endif