from time import sleep

def setup():
    # Setup pins 23 and 25 for GPIO
    fileHandle = file("/sys/class/gpio/export", "w")
    fileHandle.write("%d" % (23))
    fileHandle.write("%d" % (25))
    fileHandle.close()

    # Setup pin 23 as the camera output
    fileHandle = file("/sys/class/gpio/gpio23/direction", "w")
    fileHandle.write("out")
    fileHandle.close()

    # Setup pin 25 as the timing input (VSYNC in) using interrupts
    fileHandle = file("/sys/class/gpio/gpio25/direction", "w")
    fileHandle.write("in")
    fileHandle.close()
    fileHandle = file("/sys/class/gpio/gpio25/event", "w")
    fileHandle.write("rising")
    fileHandle.close()

def cleanup():
    # Cleans up the pins we were using and unexports them so others may use them
    fileHandle = file("/sys/class/gpio/unexport", "w")
    fileHandle.write("%d" % (23))
    fileHandle.write("%d" % (25))

def generateTimingSignal():
    # Blocking read on pin 25. Will return once we have a rising edge 
    fileHandle = file("/sys/class/gpio/gpio25/value", "r")
    fileHandle.close()

    # Generate our timing signal
    fileHandle = file("/sys/class/gpio/gpio23/value", "w")
    fileHandle.write("1")
    fileHandle.flush()
    fileHandle.write("0")

    sleep(.01)
    fileHandle.write("1")
    fileHandle.flush()
    fileHandle.write("0")

    sleep(.01)
    fileHandle.write("1")
    fileHandle.flush()
    fileHandle.write("0")

    fileHandle.close()

def main():
    setup()

    while(true):
        generateTimingSignal()

    cleanup()

if __name__ == '__main__':
    main()
