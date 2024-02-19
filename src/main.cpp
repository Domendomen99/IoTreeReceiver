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
///////////////////////////////////////////////////////////
#define MILLIS 1000000
RTC_DATA_ATTR int callbackCount = 0;
RTC_DATA_ATTR int loopCount = 0;

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

void deepSleep(int tempo){
  esp_sleep_enable_timer_wakeup(tempo * MILLIS);
  Serial.flush();
  esp_deep_sleep_start();
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
  String stringaTopicLightAttention = "domenicoRossini/IoTree/light/needAttention";
  String stringaTopicHumAttention = "domenicoRossini/IoTree/hum/needAttention";
  String stringaTopicTempAttention = "domenicoRossini/IoTree/temp/needAttention";
  if(topicStr==stringaTopicLight){
    Serial.println("Ricevuto lightMSG");
  }
  if(topicStr==stringaTopicHum){
    Serial.println("Ricevuto humMSG");
  }
  if(topicStr==stringaTopicTemp){
    Serial.println("Ricevuto tempMSG");
  }
  if(topicStr==stringaTopicLightAttention){
    Serial.println("Ricevuto lightWarning");
  }
  if(topicStr==stringaTopicHumAttention){
    Serial.println("Ricevuto humWarning");
  }
  if(topicStr==stringaTopicTempAttention){
    Serial.println("Ricevuto tempWarning");
  }
  Serial.println();

  callbackCount++;
  Serial.println(callbackCount);
  Serial.println();
  if (callbackCount==3)
  {
    callbackCount = 0;
    loopCount = 0;
    deepSleep(60);
  }

}

void inizializzaLED(){
  Serial.println("Ingresso in InizializzaLED");
  pinMode(pinLed1,OUTPUT);
  //pinMode(pinLed2,OUTPUT);
  //digitalWrite(pinLed1,HIGH);
  //digitalWrite(pinLed2,LOW);
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
  //client.subscribe("domenicoRossini/IoTree/light");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light)");
  //client.subscribe("domenicoRossini/IoTree/hum");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum)");
  //client.subscribe("domenicoRossini/IoTree/temp");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp)");
  //client.subscribe("domenicoRossini/IoTree/light/status");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light/status)");
  //client.subscribe("domenicoRossini/IoTree/hum/status");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum/status)");
  //client.subscribe("domenicoRossini/IoTree/temp/status");
  //Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp/status)");
  client.subscribe("domenicoRossini/IoTree/light/needAttention");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/light/needAttention)");
  client.subscribe("domenicoRossini/IoTree/hum/needAttention");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/hum/needAttention)");
  client.subscribe("domenicoRossini/IoTree/temp/needAttention");
  Serial.println("\n-> Iscrizione a topic (domenicoRossini/IoTree/temp/needAttention)");
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

void riconnessioneSeNecessario(){
  if (!client.connected()) {
    reconnect();
    iscrizioneTopic();
  }
}



void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);
  Serial.println("Ingresso in SETUP RECEIVER");
  connessioneaWiFi();
  inizializzaLED();
  client.setKeepAlive(30000);
  client.setCallback(callback);
}

void loop() {

  riconnessioneSeNecessario();

  client.loop();

  Serial.println("Ingresso in LOOP");

  delay(1000);

  Serial.println("Fine LOOP"); Serial.println("");

  loopCount++;
  Serial.println(loopCount);
  Serial.println();
  if (loopCount==60)
  {
    loopCount = 0;
    deepSleep(60);
  }
  

}

