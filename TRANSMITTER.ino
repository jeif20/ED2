/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define trigPin A2
#define echoPin A3

int maximumRange = 200;
int minimumRange =0;
long duration, distance;

RF24 radio(A0, A1); // CNS, CE
const byte addresses[][6] = {"00001"};
boolean buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration/58.2;

  radio.stopListening();
  int potValue = analogRead(A0);
  int angleValue = map(potValue, 0, 1023, 0, 180);
  radio.write(&angleValue, sizeof(angleValue));

  delay(5);
  radio.startListening();
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));
  
  if (distance >= maximumRange || distance <= minimumRange) {
    Serial.println("-1");
    //digitalWrite(led, HIGH);
  }
  else {
    Serial.println(distance);
    //digitalWrite(led, LOW);
  }

  delay(50);
}
