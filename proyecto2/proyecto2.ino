#include <ThingSpeak.h>

#include <ESP8266WiFi.h>

#include "secrets.h"

char ssid[] = "santiagos22";   // your network SSID (name) 
char pass[] = "cxsf3296";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long temperatureChannelNumber = SECRET_CH_ID_PF;
const char * APIkey = SECRET_READ_APIKEY_PF;
unsigned int tempFieldNumber = 1;

void setup() {

  pinMode(0,OUTPUT);
  digitalWrite(0, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);


  Serial.begin(115200);
  while(!Serial){
    ;
  }

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}


void loop() {
  int statusCode = 0;

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }

  float temperatureInF = ThingSpeak.readFloatField(temperatureChannelNumber, tempFieldNumber);

   statusCode = ThingSpeak.getLastReadStatus();

  if(statusCode == 200){
    Serial.println("Temperatura: " + String(temperatureInF) + " deg C");
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
  delay(10000); // 


  if(temperatureInF>= 26.0){
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(0,LOW);
  }else{
    digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(0,HIGH);
  }


}
