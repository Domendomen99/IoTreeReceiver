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
int pinLed1 = 13;

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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Ingresso in CALLBACK");
  digitalWrite(pinLed1,HIGH);
  delay(500);
  digitalWrite(pinLed1,LOW);
  // handle message arrived
  Serial.print(" - Message arrived on topic : [");
  Serial.print(topic);
  Serial.print("] ->  ");
  String payloaSTR="";
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    payloaSTR = payloaSTR + (char)payload[i];
  }
  Serial.println("");
  String topicStr(topic);
  String stringaTopicLight = "domenicoRossini/IoTree/light";
  String stringaTopicHum = "domenicoRossini/IoTree/hum";
  String stringaTopicTemp = "domenicoRossini/IoTree/temp";
  String stringaTopicLightStatus = "domenicoRossini/IoTree/light/status";
  String stringaTopicHumStatus = "domenicoRossini/IoTree/hum/status";
  String stringaTopicTempStatus = "domenicoRossini/IoTree/temp/status";
  if(topicStr==stringaTopicLight){
    Serial.println("Ricevuto lightMSG");
    //luminositaINT = payloaSTR.toInt();
    /*if(luminositaINT>luminosiaLimite1){
      digitalWrite(pinLed1,LOW);
      digitalWrite(pinLed2,HIGH);
    }else{
      digitalWrite(pinLed1,HIGH);
      digitalWrite(pinLed2,LOW);
    }*/
  }
  if(topicStr==stringaTopicHum){
    Serial.println("Ricevuto humMSG");
  }
  if(topicStr==stringaTopicTemp){
    Serial.println("Ricevuto tempMSG");
  }
  if(topicStr==stringaTopicTempStatus){
    Serial.println("Ricevuto tempStatMSG");
    if(payloaSTR.equals("false")){
      //statusTemp = false;
    }else{
      //statusTemp = true;
    }
  }
  if(topicStr==stringaTopicHumStatus){
    Serial.println("Ricevuto humStatMSG");
    if(payloaSTR.equals("false")){
      //statusHum = false;
    }else{
      //statusHum = true;
    }
  }
  if(topicStr==stringaTopicLightStatus){
    Serial.println("Ricevuto lightStatMSG");
    if(payloaSTR.equals("false")){
      //statusLight = false;
    }else{
      //statusLight = true;
    }
  }
  Serial.println();
}

void inizializzaLED(){
  Serial.println("Ingresso in InizializzaLED");
  pinMode(pinLed1,OUTPUT);
  //pinMode(pinLed2,OUTPUT);
  //digitalWrite(pinLed1,HIGH);
  //digitalWrite(pinLed2,LOW);
}

// put function declarations here:
//int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  Serial.println("Ingresso in SETUP");
  connessioneaWiFi();
  inizializzaLED();
  client.setKeepAlive(30000);
  client.setCallback(callback);
}

void iscrizioneTopic(){
  Serial.println("Ingresso in IscrizioneTOPIC");
  /*client.subscribe("inTopic");
  Serial.println("\n-> Iscrizione a topic (inTopic)");
  client.subscribe("outTopic");
  Serial.println("\n-> Iscrizione a topic (outTopic)");*/
  //client.subscribe("domenicoRossini/IoTree/light");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light)");
  //client.subscribe("domenicoRossini/IoTree/temp");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp)");
  //client.subscribe("domenicoRossini/IoTree/hum");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum)");
  client.subscribe("domenicoRossini/IoTree/light");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light)");
  client.subscribe("domenicoRossini/IoTree/hum");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum)");
  client.subscribe("domenicoRossini/IoTree/temp");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp)");
  client.subscribe("domenicoRossini/IoTree/light/status");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light/status)");
  client.subscribe("domenicoRossini/IoTree/hum/status");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum/status)");
  client.subscribe("domenicoRossini/IoTree/temp/status");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp/status)");
}

void reconnect() {
  Serial.println("Ingresso in reconnect");
  // Loop until we're reconnected

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect

    // codice per connessione con nome casuale
    //String clientId = "ESP8266Client-";
    //clientId += String(random(0xffff), HEX);
    
    if (client.connect("-> receiverIoTree <-")){
      Serial.println("\n-> Connessione Stabilita");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
    iscrizioneTopic();
  }
  client.loop();
  Serial.println("Ingresso in LOOP");
  //Serial.println("CIAO");
  delay(500);
}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}