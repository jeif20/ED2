/*
 Pump Fade
 
 This example shows how to increase and decrease the
 intensity of a pump as a function of time. In effect
 it's similar to the LED fading sequence but for a motor.
 
 This example code is in the public domain.
 Adapted from Basic/Fade example.
 */
int motor = 9;     //Must be PWM pin, goes to motor (gate)     
int intensity = 0; //Actual tension: 12 -(255-intensity)*5/255  
int crease = 3;  //Changes motor intensity
void setup()  {
  pinMode(motor, OUTPUT);
}
void loop()  {
  analogWrite(motor, intensity);  //Writes PWM to the motor   
  intensity = intensity + crease;
  if (intensity == 0 || intensity == 255) {
    crease = -crease ;  //Increase to decrease due to line 21
  }    
  delay(3000); //Making this too small can damage the motor                           
}
