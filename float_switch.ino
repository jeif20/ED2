// defines pins numbers
#define buzzer A0
#define float_switch A1

void setup() {
pinMode(float_switch, INPUT_PULLUP);
pinMode(buzzer, OUTPUT);

}

void loop() {
  //WATER LEVEL IN CONTAINER IS HIGH
 if(digitalRead(float_switch) == HIGH)
  {
     digitalWrite(buzzer, LOW);
  }
  
  //WATER LEVEL IN CONTAINER IS LOW
  else
  {
     digitalWrite(buzzer, HIGH);
  }

}
