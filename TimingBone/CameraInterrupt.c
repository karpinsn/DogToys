#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

int main() 
{
    struct pollfd pfd[2];

    int gpio_fd = open("/sys/class/gpio/gpio32/value", O_RDONLY);

    while (1) 
    {
	memset((void*)pfd, 0, sizeof(pfd));	

    	pfd[0].fd = STDIN_FILENO;
    	pfd[0].events = POLLIN;

    	pfd[1].fd = gpio_fd;
    	pfd[1].events = POLLPRI;

        printf("Listening for Interrupts ...\n");
        int ready = poll(pfd, 2, -1);
       
        if (ready > 0 && pfd[1].revents & POLLPRI) 
        {
            printf("Interrupt \n");
	    char *buf[200];
	   
	    // Have to read in the interrupt or it will fire again
	    int len = read(pfd[1].fd, buf, 200);
        }

	fflush(stdout);
    }

    return close(gpio_fd);
}

