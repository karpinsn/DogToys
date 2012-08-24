#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

void main() 
{
    struct pollfd pfd;

    pfd.fd = open("/sys/class/gpio/gpio70/value", O_RDONLY);
    pfd.events = POLLPRI;
    pfd.revents = 0;

    while (1) 
    {
        printf("ready: %d\n", ready);
        int ready = poll(pfd, 1, -1);
       
        if (pfd[A].revents != 0) 
        {
            printf("\t Interrupt \n");
        }
    }
}

