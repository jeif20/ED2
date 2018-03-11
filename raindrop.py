import time
import RPi.GPIO as GPIO
import urllib2
import json

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)

def sendNotification(token, channel, message):
        data = {
                "body" : message,
                "message_type" : "text/plain"
        }

        req = urllib2.Request('http://api.pushetta.com/api/pushes/{0}/'.format($
        req.add_header('Content-Type', 'application/json')
        req.add_header('Authorization', 'Token {0}' .format(token))

        response = urllib2.urlopen(req, json.dumps(data))

while True:
        input_state = GPIO.input(18)
        if input_state == False:
                print('It\'s raining')
                sendNotification("b5f5218ebe1f30d8097e6e7f18e3b3b0f1456e07","RaspiFloat", "It is raining")
                time.sleep(2) 
