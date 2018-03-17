

#include <DS3231.h>

#include <Wire.h>


//GND on the DS3231 to GND on the Arduino
//VCC on the DS3231 to the 5V pin on the Arduino
//SCL on the DS3231 to A5 on the Arduino
//SDA on the DS3231 to A4 on the Arduino

DS3231  rtc(SDA, SCL);

Time  t;



int Hor;

int Min;

int Sec;




void setup()

{  
  Wire.begin();
  rtc.begin();
  Serial.begin(115200);
  
  Serial.print("DIYHacking.com");
  Serial.print("Arduino Alarm ");

  // The following lines can be uncommented to set the date and time

  rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY

  rtc.setTime(9, 23, 0);     // Set the time to 12:00:00 (24hr format)

  rtc.setDate(3, 6, 2018);   // Set the date to January 1st, 2014

  delay(2000);

}


void loop()

{

  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;


  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating
  delay (1000);



 if( Hor == 9 &&  (Min == 5 || Min == 6)) //Comparing the current time with the Alarm time

{



Serial.print("Alarm ON");
 Serial.print("\n"); 

Serial.print("Alarming");

 Serial.print("\n"); 
} 

 delay(1000); 

}



