import RPi.GPIO as GPIO
import time #library for time
import urllib2 #importing library for pushetta(notification app)
import json #library for notification
from firebase import firebase #importing library for firebase
from functools import partial

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23, GPIO.IN) #set pin gpio 23 for raindrop sensor
GPIO.setup(10, GPIO.OUT) #set pin gpio 10 for floatswitch sensor
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP) #set pin gpio 21 for floatswitch sensor

#adding the link where all our data is going to saved whithin firebase
firebase = firebase.FirebaseApplication('https://myapp-67d2e.firebaseio.com/', None)


#this function will send the notification to the user's phone using a pushetta app when water level is low
#or when raining
def sendNotification(token, channel, message):
        data = {
                "body" : message,
                "message_type" : "text/plain"
        }

        req = urllib2.Request('http://api.pushetta.com/api/pushes/{0}/'.format(channel))
        req.add_header('Content-Type', 'application/json')
        req.add_header('Authorization', 'Token {0}' .format(token))
        response = urllib2.urlopen(req, json.dumps(data))

while True:
        input_state = GPIO.input(21) #setting gpio 21 as input for floatswitch sensor
        input_state1 = GPIO.input(23) #setting gpio 23 as input for raindrop sensor

        if input_state == False:
                GPIO.output(10,1) #when magnet drops due to water level
                water = 'Water Level Is Low' #set variable 'water' to 'water level is low'
                print 'Water Level Is Low' #the alert will be displayed everytime it is true
                sendNotification("b5f5218ebe1f30d8097e6e7f18e3b3b0f1456e07", "RaspiFloat", "Water Level Is Low") #(token, channel, message) for the notification app
                time.sleep(2) #sensor will send notification every 2 seconds when it is true
                GPIO.output(10,0) #when magnet rises by water
                time.sleep(2)
                data = {"Water":str(water)} #declare variable data to the alert
                firebase.post('/sensor/water', data) #alert('water level is low) will be posted in firebase database
                
         if input_state1 == False:
                rain = 'It\'s raining' #set variable rain to 'it is raining'
                print 'It\'s raining' #alert will be displayed everytime it is true
                sendNotification("b5f5218ebe1f30d8097e6e7f18e3b3b0f1456e07","RaspiRain", "It is raining") #(token, channel, message) for notification app
                time.sleep(4) #sensor will send notification every 4 seconds when it is true 
                result = {"Rain":str(rain)} #declare variable result to the alert
                firebase.post('/sensor/rain', result) #alert('it is raining') will be posted in firebase database
