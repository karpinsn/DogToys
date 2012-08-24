from time import sleep
from bbio import *
 
def setup():    
    print "Initializing GPIO1_17 as camera trigger output"
    pinMode(GPIO1_17, OUTPUT)

    print "Initializing GPIO3_21 as VSYNC timing input"
    pinMode(GPIO3_21, INPUT)
 
def loop():
    if(HIGH == digitalRead(GPIO3_21)):
        digitalWrite(GPIO1_17, HIGH)
        digitalWrite(GPIO1_17, LOW)

        sleep(.01)
        digitalWrite(GPIO1_17, HIGH)
        digitalWrite(GPIO1_17, LOW)

        sleep(.01)
        digitalWrite(GPIO1_17, HIGH)
        digitalWrite(GPIO1_17, LOW)
    sleep(.01) 

if __name__ == '__main__':
    run(setup, loop)
