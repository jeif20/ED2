import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)


while True:
        input_state = GPIO.input(18)
        if input_state == False:
                print('It\'s raining')
                time.sleep(2) 
