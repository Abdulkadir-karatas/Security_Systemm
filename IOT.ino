#define BLYNK_TEMPLATE_ID "**********"
#define BLYNK_TEMPLATE_NAME "SECURİTY"
#define BLYNK_AUTH_TOKEN "***********"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = "********";
char ssid[] = "********"; // WiFi ağ adınızı buraya yazın
char pass[] = "********"; // WiFi şifrenizi buraya yazın

SimpleTimer timer;

void myTimerEvent() {
  Blynk.virtualWrite(V1, millis() / 1000);
}

int pirsensor = D0;
int irsensor = D1;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pirsensor, INPUT_PULLUP);
  pinMode(irsensor, INPUT);
  timer.setInterval(1000L, sensorvalue1);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sensorvalue1() {
  if (digitalRead(pirsensor) == HIGH) {
    Blynk.virtualWrite(V2, 255);
    Blynk.virtualWrite(V4, "PIR sensöründe hareket tespit edildi!!!");
    Blynk.logEvent("pir_hareket", "PIR sensöründe hareket tespit edildi!!!");
  } 
  if (digitalRead(pirsensor) == LOW) {
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V4, "PIR Normal");
  }
  if (digitalRead(irsensor) == LOW) {
    Blynk.virtualWrite(V3, 255);
    Blynk.virtualWrite(V4, "IR sensöründe hareket tespit edildi!!!");
    Blynk.logEvent("ir_hareket", "IR sensöründe hareket tespit edildi!!!");
  } 
  if (digitalRead(irsensor) == HIGH) {
    Blynk.virtualWrite(V3, 0);
  }
}
