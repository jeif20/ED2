import i2c_LCD_driver
import sys
import Adafruit_DHT
from firebase import firebase

import urllib2, urllib, httplib
import json
import os 
from functools import partial

from time import *

mylcd = i2c_LCD_driver.lcd()

#we insert a link provided in firebase
firebase = firebase.FirebaseApplication('https://myapp-67d2e.firebaseio.com/', None)

def update_firebase():

        humidity, temperature = Adafruit_DHT.read_retry(11, 4)
        mylcd.lcd_display_string("Temp: %d C" % temperature, 1, 0)
        mylcd.lcd_display_string("Humidity: %d.0 %%" % humidity, 2, 0)
        print 'Temp: {0:0.1f} C  Humidity: {1:0.1f} %'.format(temperature, humidity)

        data = {"Temp": temperature, "Humidity": humidity}
        firebase.post('/sensor/humiditytemp', data)

while True:
        update_firebase()
        sleep(20)
