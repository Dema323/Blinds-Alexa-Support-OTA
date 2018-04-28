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

void StartUp();
void StopUp();
void StartDown();
void StopDown();
void WriteVirtual();

void StartUp(){
  eventTime = huidige tijd
  String currentTime = String(hour()) + ":" + minute() + ":" + second() + " - Started moving up";
  terminal.println(currentTime);
  terminal.flush();
}

void StopUp(){
  String currentTime = String(hour()) + ":" + minute() + ":" + second() + " - Stopped moving up";
  terminal.println(currentTime);
  terminal.flush();
}

void StartDown(){
  String currentTime = String(hour()) + ":" + minute() + ":" + second() + " - Started moving down";
  terminal.println(currentTime);
  terminal.flush();
}

void StopDown(){
  String currentTime = String(hour()) + ":" + minute() + ":" + second() + " - Stopped moving down";
  terminal.println(currentTime);
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

 void WriteVirtual(){
   Blynk.virtualWrite(V10, 25);
 }

void setup()
{
  setSyncInterval(1);
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    delay(1000);
  }
  setSyncInterval(900000);
  ArduinoOTA.begin();
  rtc.begin();
  timer.setInterval(500, WriteVirtual);
  terminal.println("Device online");
  terminal.flush();
}
void loop()
{
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();

}
