import i2c_LCD_driver #library for the lcd
import sys
import Adafruit_DHT #library for the humidity and temperature sensor
from firebase import firebase #library for firebase

import urllib2, urllib, httplib
import json
import os 
from functools import partial

from time import *

mylcd = i2c_LCD_driver.lcd()

#use the link provide by firebase so we can store our data within the firebase database
firebase = firebase.FirebaseApplication('https://myapp-67d2e.firebaseio.com/', None)

#this function will help us to display the updated changes that the sensor will send
def update_firebase():

        humidity, temperature = Adafruit_DHT.read_retry(11, 4)
        mylcd.lcd_display_string("Temp: %d C" % temperature, 1, 0) #value of the temperature will be displayed in the first row of the lcd
        mylcd.lcd_display_string("Humidity: %d.0 %%" % humidity, 2, 0) #value of the humidity will be displayed in the second row of the lcd
        print 'Temp: {0:0.1f} C  Humidity: {1:0.1f} %'.format(temperature, humidity)

        data = {"Temp": temperature, "Humidity": humidity} #set variable data to the humidity and temperature values
        firebase.post('/sensor/humiditytemp', data) #the values will be posted in firebase database 

while True:
        update_firebase() #the values will be updated every 20 seconds, however time can be modified
        sleep(20)
