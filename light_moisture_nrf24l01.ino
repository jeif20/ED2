#include <SPI.h>
#include <nRF24L01.h> //library for the wireless transceiver nrf24l01
#include <RF24.h> //library for the wireless transceiver nrf24l01
#include <Wire.h>
#include <LCD.h> // library for the lcd with a module
#include <LiquidCrystal_I2C.h>  // library for the lcd with a module

LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); 

RF24 radio(7, 8); // CE, CSN for the nrf24l01
const byte address[6] = "00001"; //00001 is a password so it can communicate with the other nrf24l01

int photo_pin = 2;  //set pin d2 to the photocell as input
int minLight;   //calibrate to the min reading
int maxLight;   //calibrate to the max reading
int lightLevel;   //determine the level of light
float adjustedLightLevel; 

int moisture_pin = A0;  //set pin A0 to the moisture sensor as input
float moisture_value ;  //mositure output value

void setup() {
  
    Serial.begin(9600); //the values sent by the sensor can be monitored

    //SETUP THE LCD
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);   //turn the backlight on by setting it to HIGH
    lcd.begin(16, 2);
    lcd.clear();

    //SETTING UP THE NRF24L01
    radio.begin(); //nrf is ready to send values
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

    //Setup the starting light level limits
    lightLevel=analogRead(photo_pin);  //the level of light will be set to a certain value
    minLight=lightLevel-20; //determine the min level of light
    maxLight=lightLevel;  //determine the max level of light
 
    lcd.print("Light:  Moisture:"); //values of the sensors will be displayed in the lcd screen
}
void loop() {
  
     lcd.setCursor(0, 1); //moisture name and value will be displayed at the begining of the screen
     moisture_value= analogRead(moisture_pin); //moisture sensor reading
     moisture_value = map(moisture_value,550,0,0,100);
   
     //auto-adjust the minimum and maximum limits in real time
     lightLevel=analogRead(photo_pin);
     if(minLight>lightLevel){ //when it is dark
        minLight=lightLevel;
     }
     if(maxLight<lightLevel){ // when it is light
        maxLight=lightLevel;
     }
     
     adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100); //Adjust the light level to produce a result between 0 and 100.
 
     lcd.print(adjustedLightLevel); //the light level will be displayed in the lcd screen
     lcd.setCursor(7,1);  //light name and value will be in the middle of the screen
     lcd.print(moisture_value); //values of moisture sensor will be displayed in the lcd screen
     delay(5000); //values will update every 5 minutes
    
    //int potValue = analogRead(A0);
     radio.write(&moisture_value, sizeof(moisture_value)); //nrf24l01 will start transmitting values from sensors
     Serial.println(moisture_value);  //values can be displayed by the serial monitor

     delay(5);
}
