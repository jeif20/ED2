#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 8); // CNS, CE
const byte addresses[][6] = {"00001"};
Servo myServo;
boolean buttonState = 0;

void setup() {
  myServo.attach(5);
  radio.begin();
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      myServo.write(angleV);
    }
    delay(5);
    radio.stopListening();
    radio.write(&buttonState, sizeof(buttonState));
  }
}
