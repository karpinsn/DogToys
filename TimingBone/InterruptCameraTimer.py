from time import sleep
from poll import *
from bbio import *
 
def configInterrupt(pin):
    fileHandle = file("/sys/class/gpio/export", "w")
    fileHandle.write("%d" % pin)
    fileHandle.close()

    fileHandle = file("/sys/class/gpio/gpioXXX/direction", "w")
    fileHandle.write("in")
    fileHandle.close()

    fileHandle = file("/sys/class/gpio/gpioXXX/edge", "w")
    fileHandle.write("rising")
    fileHandle.close()

def setup():    
    print "Initializing GPIO1_17 as camera trigger output"
    pinMode(GPIO1_4, OUTPUT)

    print "Initializing GPIO3_21 as VSYNC timing input"
    configInterrupt(GPIO1_0)
 
def loop():

    struct pollfd pfd
    pfd.fd = open("/sys/class/gpio/gpioXXX/value", "r")
    pfd.events = POLLPRI
    pfd.revents = 0

    ready = poll(pfd, 1, -1)

    if(0 != pfd.revents):
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
