def cleanup():
    # Cleans up the pins we were using and unexports them so others may use them
    fileHandle = file("/sys/class/gpio/unexport", "w")
    fileHandle.write("%d" % (49))
    fileHandle.close()

    fileHandle = file("/sys/class/gpio/unexport", "w")
    fileHandle.write("%d" % (117))
    fileHandle.close()

def main():
    cleanup()

if __name__ == '__main__':
    main()
