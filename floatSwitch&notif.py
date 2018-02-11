

import RPi.GPIO as GPIO
import time
import urllib2
import json
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(10, GPIO.OUT)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

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
        input_state = GPIO.input(21)
        if input_state == False:
                GPIO.output(10,1)
                print('Water Level Is Low')
                sendNotification("b5f5218ebe1f30d8097e6e7f18e3b3b0f1456e07", "RaspiFloat", "Water Level Is Low")
                time.sleep(3600)
                GPIO.output(10,0)
                time.sleep(2)