#include <M5Stack.h>
#include "Ultrasonic.h"
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "AsyncUDP.h"

#define NBSENSOR_MAX 11
#define DELAY 10
#define CROSSING_TIME 50
#define TIME_BTW 20
#define BG_COLOR 0xa254
#define TEXT_COLOR 0xfbe4

Ultrasonic in(21);
Ultrasonic out(22);

long range_in;
long range_out;

int c_in = 0;
int c_out = 0;
int t_in = 0;
int t_out = 0;

long timer = 0;
long time_btw = 0;

const char * ssid = "jpp";
const char * password = "wiiwiiwii2007";
AsyncUDP udp;
HTTPClient http;
String ip = "192.168.43.5";
typedef struct{
  uint8_t nbPersonneEntree;
  uint8_t nbPersonneSortie;
} info_magasin;

info_magasin magasin1;

void setup()
{
   magasin1.nbPersonneEntree = 0;
   magasin1.nbPersonneSortie = 0;
   delay(150);
   M5.begin();
   //Serial.begin(115200);
   delay(10);
   // We start by connecting to a WiFi network
   //Serial.println();
   //Serial.println();
   //Serial.print("Connecting to ");
   //Serial.println(ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  //Serial.println();

  delay(100);
}
void loop()
{
  
  range_in = in.MeasureInCentimeters();
  range_out = out.MeasureInCentimeters();
  
  M5.Lcd.fillScreen(BG_COLOR);
  M5.Lcd.drawLine(160,10,160,230,TEXT_COLOR);
  M5.Lcd.setTextSize(250);
  M5.Lcd.setTextColor(TEXT_COLOR);
  
  char str_entree[5];
  char str_sorti[5];
  sprintf(str_entree, "%d",  magasin1.nbPersonneEntree);
  sprintf(str_sorti, "%d",  magasin1.nbPersonneSortie);
  //Serial.println(str_entree);
  
  M5.Lcd.drawString(str_entree, 55, 80, 2);
  M5.Lcd.drawString(str_sorti, 215, 80, 2);
  M5.Lcd.setTextSize(3);
  M5.Lcd.drawString("Entrees", 15, 30, 2);
  M5.Lcd.drawString("Sorties", 175, 30, 2);
  
  //Serial.print("In : ");
  //Serial.println(range_in);
  //Serial.print("Out : ");
  //Serial.println(range_out);
  //Serial.print("Entree : ");
  //Serial.println(entree);
  //Serial.print("Sorti : ");
  //Serial.println(sorti);

  compteur();
  delay(DELAY);
}

void compteur() {

  time_btw++;
  
  if(range_in<60 && time_btw > TIME_BTW && t_out == 0){
    t_in = 1;
    //M5.Lcd.println(range_in);
  }

  if(range_out<60 && time_btw > TIME_BTW && t_in == 0){
    t_out = 1;
  }

  if(range_in<50){
    c_in = 1;
  }

  if(range_out<50){
    c_out = 1;
  }

  //Serial.print("c_in : ");
  //Serial.println(c_in);
  //Serial.print("c_out : ");
  //Serial.println(c_out);
  
  if(t_in){
    //Serial.println("in");
    timer++;
    //Serial.println(timer);
    if(timer<CROSSING_TIME){
      if(c_out) {
        if(magasin1.nbPersonneSortie<magasin1.nbPersonneEntree) {
          magasin1.nbPersonneSortie++;
          http.begin("http://"+ip+":8081/client/leave"); //HTTP
          int httpCode = http.POST("");
          //Serial.println(httpCode);
          //Serial.print("Sorti : ");
          //Serial.println(sorti);
          t_in = 0;
          t_out = 0;
          c_out = 0;
          c_in = 0;
          time_btw = 0;
        }
      }
    }
    else {
      t_in = 0;
      c_in = 0;
      timer = 0;
    }
  }
  
  if(t_out){
    //Serial.println("out");
    timer++;
    if(timer<CROSSING_TIME){
      if(c_in) {
         magasin1.nbPersonneEntree++;
         http.begin("http://"+ip+":8081/client/enter"); //HTTP
         int httpCode = http.POST("");
         //Serial.println(httpCode);
         
        //Serial.print("Entree : ");
        //Serial.println(entree);
        
        t_in = 0;
        t_out = 0;
        c_in = 0;
        c_out = 0;
        time_btw = 0;
      }
    }
    else {
      t_out = 0;
      c_out = 0;
      timer = 0;
    }
  }
}


