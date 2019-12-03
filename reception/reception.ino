#include <HTTPClient.h>

#include <M5Stack.h>
#include <Wire.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "AsyncUDP.h"
#define NBSENSOR_MAX 11

const char * ssid = "jpp";
const char * password = "wiiwiiwii2007";
AsyncUDP udp;
HTTPClient http;
char *ip=;
uint8_t nbPersonne;

void printLCD();

uint32_t now;

void setup() {
  nbPersonne=0;
  delay(150);
  M5.begin();
  now = millis();
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(100);

}

void loop() {
  if(millis() - now > 1000){
    now = millis();
    http
    //udp.writeTo((uint8_t*)&magasin1, sizeof(info_magasin),ip,8080);
     http.begin("http://"+ip+":8081/client/M5"); //HTTP
     int httpCode = http.GET();
     Serial.println(httpCode);
    //printLCD();
    if(M5.BtnA.wasPressed()){
    //  nbsensor = 1;
    }
  }
}

/*
void printLCD(){
  char data[50];
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawLine(0, 0, 0, 239, TFT_RED);
  M5.Lcd.drawLine(80, 0, 80, 239, TFT_RED);
  M5.Lcd.drawLine(160, 0, 160, 239, TFT_RED);
  M5.Lcd.drawLine(240, 0, 240, 239, TFT_RED);
  M5.Lcd.drawLine(319, 0, 319, 239, TFT_RED);
  M5.Lcd.drawLine(0, 0, 319, 0, TFT_RED);
  M5.Lcd.drawLine(0, 80, 319, 80, TFT_RED);
  M5.Lcd.drawLine(0, 160, 319, 160, TFT_RED);
  M5.Lcd.drawLine(0, 239, 319, 239, TFT_RED);
  for (int y = 0, i = 0  ; y < 3 && i < nbsensor ; y++){
    for (int x = 0; x < 4 && i < nbsensor ; x++, i++){ 
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.setTextSize(2);
      sprintf(data, "%2.1f", sensors[i].temp);
      M5.Lcd.drawString(data, 40 + 80 * x, 20 + 80 * y, 1);
      sprintf(data, "%2.1f", sensors[i].hum);
      M5.Lcd.drawString(data, 40 + 80 * x, 40 + 80 * y, 1);
      sprintf(data, "%02x%02x%02x%02x%02x%02x", sensors[i].mac[0], sensors[i].mac[1], sensors[i].mac[2], sensors[i].mac[3], sensors[i].mac[4], sensors[i].mac[5]);
      M5.Lcd.setTextSize(1);
      M5.Lcd.drawString(data, 40 + 80 * x, 60 + 80 * y, 1);
     }
  }
}*/
#include <HTTPClient.h>

#include <M5Stack.h>
#include <Wire.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "AsyncUDP.h"
#define NBSENSOR_MAX 11

const char * ssid = "jpp";
const char * password = "wiiwiiwii2007";
AsyncUDP udp;
HTTPClient http;
char *ip=;
typedef struct{
  uint8_t nbPersonneEntree;
  uint8_t nbPersonneSortie;
} info_magasin;

info_magasin magasin1;

void printLCD();
IPAddress ip = IPAddress(192,168,56,1);
uint32_t now;

void setup() {
  magasin1.nbPersonneEntree = 0;
  magasin1.nbPersonneSortie = 0;
  delay(150);
  M5.begin();
  now = millis();

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /*byte mac[6];
  WiFi.macAddress(mac);
  Serial.println("MAC address: ");
  for(int i = 5; i >= 0; --i){
    Serial.print(mac[i], HEX);
    sensors[0].mac[i] = mac[i];
  }*/
  
  Serial.println();

  delay(100);
/*
  if(udp.connect(IPAddress(192,168,1,255), 1234)) {
    Serial.println("UDP connected");
  }
*/
  
}

void loop() {
  if(millis() - now > 1000){
    now = millis();
    //ici on met à jour les données
    //udp.writeTo((uint8_t*)&magasin1, sizeof(info_magasin),ip,8080);
     http.begin("http://"+ip+":8081/client"); //HTTP
     int httpCode = http.GET();
     Serial.println(httpCode);
     String payload = http.getString();
     
    //printLCD();
  }
}
/*
void printLCD(){
  char data[50];
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawLine(0, 0, 0, 239, TFT_RED);
  M5.Lcd.drawLine(80, 0, 80, 239, TFT_RED);
  M5.Lcd.drawLine(160, 0, 160, 239, TFT_RED);
  M5.Lcd.drawLine(240, 0, 240, 239, TFT_RED);
  M5.Lcd.drawLine(319, 0, 319, 239, TFT_RED);
  M5.Lcd.drawLine(0, 0, 319, 0, TFT_RED);
  M5.Lcd.drawLine(0, 80, 319, 80, TFT_RED);
  M5.Lcd.drawLine(0, 160, 319, 160, TFT_RED);
  M5.Lcd.drawLine(0, 239, 319, 239, TFT_RED);
  for (int y = 0, i = 0  ; y < 3 && i < nbsensor ; y++){
    for (int x = 0; x < 4 && i < nbsensor ; x++, i++){ 
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.setTextSize(2);
      sprintf(data, "%2.1f", sensors[i].temp);
      M5.Lcd.drawString(data, 40 + 80 * x, 20 + 80 * y, 1);
      sprintf(data, "%2.1f", sensors[i].hum);
      M5.Lcd.drawString(data, 40 + 80 * x, 40 + 80 * y, 1);
      sprintf(data, "%02x%02x%02x%02x%02x%02x", sensors[i].mac[0], sensors[i].mac[1], sensors[i].mac[2], sensors[i].mac[3], sensors[i].mac[4], sensors[i].mac[5]);
      M5.Lcd.setTextSize(1);
      M5.Lcd.drawString(data, 40 + 80 * x, 60 + 80 * y, 1);
     }
  }
}*/

