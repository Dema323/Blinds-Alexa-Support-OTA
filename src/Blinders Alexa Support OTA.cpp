#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#define BLYNK_PRINT Serial

char auth[] = "c1b5ca348c734e5fabd12fb4cceba4b2";

char ssid[] = "WiFi-2.4-D4F0";
char pass[] = "A26YXkP73nuz";

BlynkTimer timer;
WidgetTerminal terminal(V8);
WidgetRTC rtc;

int eventTime;
int eventStart;
int eventStop;
int travelTime = 31000;
bool init_status = false;
String currentTime;
int standTime = 31;

void StartUp();
void StopUp();
void StartDown();
void StopDown();
void StartInit();

void StartUp(){
  eventStart = now();
}

void StopUp(){
  eventStop = now();
  eventTime = eventStop - eventStart;
  standTime = standTime + eventTime;
  if(standTime > 31){
    standTime = 31;
  }
  double procent = (double)standTime/31;
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  Blynk.virtualWrite(V10, procent);
  terminal.println("Open at " + String(procent) +  " procent ");
  terminal.flush();
}

void StartDown(){
  eventStart = now();
}

void StopDown(){
  eventStop = now();
  eventTime = eventStop - eventStart;
  standTime = standTime - eventTime;
  if(standTime < 0){
    standTime = 0;
  }
  double procent = (double)standTime/31;
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  Blynk.virtualWrite(V10, procent);
  terminal.println("Open at " + String(procent) +  " procent ");
  terminal.flush();
}

BLYNK_WRITE(V2) //DOWN
{
 if (param.asInt()){
  digitalWrite(12, LOW);
  Blynk.virtualWrite(V3, LOW);
  delay(1000);
  StartDown();
  digitalWrite(13, HIGH);
 }else{
  StopDown();
  digitalWrite(13, LOW);
 }
 }
 BLYNK_WRITE(V3) //UP
 {
   if (param.asInt()){
  digitalWrite(13, LOW);
  Blynk.virtualWrite(V2, LOW);
  delay(1000);
  StartUp();
  digitalWrite(12, HIGH);
 }else{
  StopUp();
  digitalWrite(12, LOW);
 }
 }
  BLYNK_WRITE(V4)
   {
     if (param.asInt()){
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  Blynk.virtualWrite(V2, LOW);
  Blynk.virtualWrite(V3, LOW);
 }
 }

void StartInit(){
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(12, HIGH);
  delay(30000);
  digitalWrite(12, LOW);
  init_status = false;
  }

void setup()
{
  init_status = true;
  setSyncInterval(1);
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    delay(1000);
  }
  setSyncInterval(900000);
  ArduinoOTA.begin();
  rtc.begin();
  Blynk.virtualWrite(V8, "clr");
  StartInit();
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  terminal.println(" " + currentTime + " - Blinds to default ");
  terminal.flush();
  Blynk.virtualWrite(V10, 100);
}
void loop()
{
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
  if(init_status == true){

  }

}
