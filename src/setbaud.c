/*
 * setbaud
 * GPL-3.0 License
 * 
 * J. Schmitz, 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>

int main(int argc, char **argv) {
    int tty, ispeed, ospeed;
    struct termios2 tio;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: setbaud <terminal device> [input/output baud rate]\n");
        fprintf(stderr, "       setbaud <terminal device> <input baud rate> <output baud rate>\n");
        fprintf(stderr, "Specifying only the device, prints the currently set rates.\n");
        return 1;
    }
    
    if (argc > 2) {
        ispeed = strtol(argv[2], NULL, 0);
        if (argc > 3) {
            ospeed = strtol(argv[3], NULL, 0);
        } else {
            ospeed = ispeed;
        }
        
        if (ispeed <= 0 || ospeed <= 0) {
            fprintf(stderr, "setbaud: illegal rate\n");
            return 1;
        }
    }
    
    if ((tty = open(argv[1], (argc > 2 ? O_RDWR : O_RDONLY) | O_NOCTTY)) != -1) {
        if (ioctl(tty, TCGETS2, &tio) == -1) {
            perror("setbaud: TCGETS2");
            return 3;
        }
        
        if (argc > 2) {
            // makeraw (from glibc/termios/cfmakeraw.c)
            tio.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
            tio.c_oflag &= ~OPOST;
            tio.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
            tio.c_cflag &= ~(CSIZE|PARENB|CBAUD);  // ~CBAUD and
            tio.c_cflag |= CS8|BOTHER;             // BOTHER for custom rate
            tio.c_cc[VMIN] = 1;		/* read returns when one char is available.  */
            tio.c_cc[VTIME] = 0;
            
            // rate
            tio.c_ispeed = ispeed;
            tio.c_ospeed = ospeed;
            
            if (ioctl(tty, TCSETS2, &tio) == -1) {
                perror("setbaud: TCSETS2");
                return 4;
            }
        } else {
            fprintf(stderr, "setbaud: %s: input/output: %d/%d baud\n", argv[1], tio.c_ispeed, tio.c_ospeed);
        }
        
        close(tty);
    } else {
        fprintf(stderr, "setbaud: %s: %s\n", argv[1], strerror(errno));
        return 2;
    }
    
    return 0;
}
