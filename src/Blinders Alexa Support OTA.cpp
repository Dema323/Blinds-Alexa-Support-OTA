#include <ArduinoOTA.h>
#include <Arduino.h>
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "c1b5ca348c734e5fabd12fb4cceba4b2";

char ssid[] = "WiFi-2.4-D4F0";
char pass[] = "A26YXkP73nuz";

BlynkTimer timer;

int Height;

void UPHeightCounter();
void DOWNHeightCounter();
void WriteVirtual();

void UPHeightCounter(){
  Height++;
}

void DOWNHeightCounter(){
  Height--;
}

BLYNK_WRITE(V2) //DOWN
{
 if (param.asInt()){
  digitalWrite(12, LOW);
  Blynk.virtualWrite(V3, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  timer.setInterval(1000, DOWNHeightCounter);
 }else{
  digitalWrite(13, LOW);
 }
 }
 BLYNK_WRITE(V3) //UP
 {
   if (param.asInt()){
  digitalWrite(13, LOW);
  Blynk.virtualWrite(V2, LOW);
  delay(1000);
  digitalWrite(12, HIGH);
  timer.setInterval(1000, UPHeightCounter);
 }else{
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
   Blynk.virtualWrite(V10, Height);
 }

void setup()
{
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {}
  ArduinoOTA.begin();
  timer.setInterval(500, WriteVirtual);
}
void loop()
{
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
}
