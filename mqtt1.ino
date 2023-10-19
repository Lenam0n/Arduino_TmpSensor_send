#include <WiFi.h>
#include "DHT.h"
#include <PubSubClient.h>
#include <Wire.h>
#include "config.h"
#include "wifi_cfg.h"
#include "dht_cfg.h"

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;


void setup() {
  Serial.begin(115200);
   
  if(wifi() == true && dht_start() == true){
    client.setServer(mqtt_server, mqtt_port);    
  }else{
    Serial.println("FEHLER!");
    delay(2000);
    Serial.end();}

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("esp32DHT")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  char charbuff[10];
  //strtok(dht_val,";");
  client.loop();
  //Serial.println(dht_val);
  client.publish("testtopic/tempreture", dht_run());
  delay(2000);
  }