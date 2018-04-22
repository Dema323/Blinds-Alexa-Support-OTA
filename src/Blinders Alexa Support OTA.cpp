#include <ArduinoOTA.h>
#include <Arduino.h>
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xxxxx";

char ssid[] = "xxxxx";
char pass[] = "xxxxx";


BLYNK_WRITE(V2)
{
 if (param.asInt()){
  digitalWrite(D5, LOW);
  Blynk.virtualWrite(V3, LOW);
  delay(1000);
  digitalWrite(D1, HIGH);
 }else{
  digitalWrite(D1, LOW);
 }
 }
 BLYNK_WRITE(V3)
 {
   if (param.asInt()){
  digitalWrite(D1, LOW);
  Blynk.virtualWrite(V2, LOW);
  delay(1000);
  digitalWrite(D5, HIGH);
 }else{
  digitalWrite(D5, LOW);
 }
 }
  BLYNK_WRITE(V4)
   {
     if (param.asInt()){
  digitalWrite(D5, LOW);
  Blynk.virtualWrite(V2, LOW);
  Blynk.virtualWrite(V3, LOW);
  digitalWrite(D1, LOW);
 }
 }

void setup()
{
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {}
  ArduinoOTA.begin();
}
void loop()
{
  Blynk.run();
  ArduinoOTA.handle();

}
//
