#include <Arduino.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
//#include <string.h>

///////////////////////////////////////////////////////////
const char* nomeRete = "FASTWEB-1-A91631_EXT";
const char* pwdRete = "4452CC2BAB";
///////////////////////////////////////////////////////////
IPAddress ip_scheda(192,168,1,106);
IPAddress ip_server(192,168,1,86);
///////////////////////////////////////////////////////////
WiFiClient wifiClient;
PubSubClient client(ip_server,1883,wifiClient);
///////////////////////////////////////////////////////////

void connessioneaWiFi(){
  Serial.println("Ingresso in CONNESSIONE_WIFI");
  WiFi.mode(WIFI_STA);
  WiFi.begin(nomeRete,pwdRete);
  Serial.println("\nTentativo di connessione alla rete");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
  }
  Serial.println("\nConnessione Stabilita con IP : ");
  Serial.println(WiFi.localIP());
}

// put function declarations here:
//int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  Serial.println("Ingresso in SETUP");
  connessioneaWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Ingresso in LOOP");
  Serial.println("CIAO");
  delay(5000);
}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}