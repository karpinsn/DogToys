from time import sleep
from bbio import *
 
def setup():    
    print "Initializing GPIO1_17 as camera trigger output"
    pinMode(GPIO1_4, OUTPUT)

    print "Initializing GPIO3_21 as VSYNC timing input"
    pinMode(GPIO1_0, INPUT)
 
def loop():
    if(HIGH == digitalRead(GPIO1_0)):
        digitalWrite(GPIO1_4, HIGH)
        digitalWrite(GPIO1_4, LOW)

        sleep(.01)
        digitalWrite(GPIO1_4, HIGH)
        digitalWrite(GPIO1_4, LOW)

        sleep(.01)
        digitalWrite(GPIO1_4, HIGH)
        digitalWrite(GPIO1_4, LOW)
    sleep(.01) 

if __name__ == '__main__':
    run(setup, loop)
