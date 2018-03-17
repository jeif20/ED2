
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); 

int photoRPin = 2; 
int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int lightLevel;
float adjustedLightLevel;

int sensor_pin = A0;

float output_value ;

void setup() {
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
    lcd.begin(16, 2);
    lcd.clear();
    
 Serial.begin(9600);
 
 //Setup the starting light level limits
 lightLevel=analogRead(photoRPin);
 minLight=lightLevel-20;
 maxLight=lightLevel;
 
 lcd.print("Light:  Moisture:");
}

void loop(){
   lcd.setCursor(0, 1);
   
   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);
   
 //auto-adjust the minimum and maximum limits in real time
 lightLevel=analogRead(photoRPin);
 if(minLight>lightLevel){
 minLight=lightLevel;
 }
 if(maxLight<lightLevel){
 maxLight=lightLevel;
 }
 
 //Adjust the light level to produce a result between 0 and 100.
 adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100); 
Serial.println(adjustedLightLevel);
  lcd.print(adjustedLightLevel);
   lcd.setCursor(7,1);
   lcd.print(output_value);
    delay(5000);


}
