#include <Servo.h>
#include <ESP8266WiFi.h>
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>

// Autentication Token Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6V4t_lJlh"
#define BLYNK_TEMPLATE_NAME "Smart garden"
#define BLYNK_AUTH_TOKEN "qw56Kp7FkVtkuZg6XnlaBosFyyNPWbOs"


char ssid[] = "Studio_1";
char pass[] = "rikimaru2020";

// Pin initiation
int LED = 4; // Pin D2
int buzzer = 0; // Pin D3
int SoilHumidity = A0;
int relay1 = 14; // D5
int relay2 = 12; // D6
int button;

BlynkTimer timer;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(LED, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  servo.attach(2); // Pin D4
  timer.setInterval(100L, sendSensor);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  

}

// ============================

// Sensor Humidity
void sendSensor(){
 int value = analogRead(SoilHumidity);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V3, value); 
}

BLYNK_WRITE(V0){
  int i = 0;
  button = param.asInt();
  if(button == 1){
    digitalWrite(LED, HIGH);

    do {
      i++;
      tone(buzzer, HIGH);
      delay(60);
      noTone(buzzer);
      delay(60);

      }while (i<2);
      // delay(1000);

  }else{
    digitalWrite(LED, LOW);
    tone(buzzer, HIGH);
    delay(60);
    noTone(buzzer);
    delay(60);
  }
}

// Servo
BLYNK_WRITE(V2){
  servo.write(param.asInt());

}

// Relay 1
BLYNK_WRITE(V1){
  int i = 0;
  int pinValue = param.asInt();

  if (pinValue == 1){
    digitalWrite(relay1, LOW);
     do {
      i++;
      tone(buzzer, HIGH);
      delay(60);
      noTone(buzzer);
      delay(60);

      }while (i<2);
      // delay(1000);

  }else{
    digitalWrite(relay1, HIGH);
  }
  // Blynk.virtualWrite(V1, pinValue);
}

// Relay 2
BLYNK_WRITE(V5){
  int i = 0;
  int pinValue = param.asInt();

  if (pinValue == 1){
    digitalWrite(relay2, LOW);
     do {
      i++;
      tone(buzzer, HIGH);
      delay(60);
      noTone(buzzer);
      delay(60);

      }while (i<2);
      // delay(1000);

  }else{
    digitalWrite(relay2, HIGH);
  }
  // Blynk.virtualWrite(V1, pinValue);
}

// ======================

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
