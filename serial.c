#include "serial.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>


FUNCT_ATTR int set_iface_attribs(int fd, int speed, int parity) {
    struct termios device;
    memset (&device, 0, sizeof device);
    if (tcgetattr(fd, &device) != 0) {
        perror("Error in tcgetattr");
        return -1;
    }

    cfsetospeed(&device, speed);
    cfsetispeed(&device, speed);

    device.c_cflag = (device.c_cflag & ~CSIZE) | CS8;
    device.c_iflag &= ~IGNBRK;
    device.c_lflag = 0;
    device.c_oflag = 0;
    device.c_cc[VMIN]  = 0;
    device.c_cc[VTIME] = 5;
    device.c_iflag &= ~(IXON | IXOFF | IXANY);
    device.c_cflag |= (CLOCAL | CREAD);
    device.c_cflag &= ~(PARENB | PARODD);
    device.c_cflag |= parity;
    device.c_cflag &= ~CSTOPB;
    device.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &device) != 0) {
        perror("Error in tcsetattr");
        return -1;
    }
    return 0;
}

FUNCT_ATTR int set_blocking_mode(int fd, int block) {
    struct termios device;
    memset(&device, 0, sizeof device);
    if (tcgetattr(fd, &device) != 0) {
        perror("Error in tcgetattr");
        return -1;
    }

    device.c_cc[VMIN]  = block ? 1 : 0;
    device.c_cc[VTIME] = 5;

    if (tcsetattr(fd, TCSANOW, &device) != 0) {
        perror("Error setting term attributes");
        return -1;
    }
    return 0;
}

FUNCT_ATTR int init_device(const char * const path, int speed) {
    if (NULL == path) return -1;
    int fd = open(path, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("Can't open device");
        return -1;
    }
    if (set_iface_attribs(fd, speed, 0) < 0) return -1;
    if (set_blocking_mode(fd, 0) < 0) return -1;
    return fd;
}

ssize_t send(int fd, const char * const cmd, ssize_t size) {
	if (fd < 0 || !cmd || !size) return 0;
	ssize_t n = write(fd, cmd, size);
	usleep(2500*size);
    tcdrain(fd);
	return n;
}

ssize_t receive(int fd, char * const buff, size_t size) {
	if (fd < 0 || !buff || !size) return 0;
	size_t sz = 0, n_read = 0;
	while ((n_read = read(fd, buff+sz, size-sz)) > 0) {
		sz += n_read;
		if (sz >= size) {
			buff[size-1] = '\0';
			return (ssize_t)(size-1);
		}
	}
    // search for '\r' or '\r\n' at the end of packet:
	while (buff[sz-1] == '\r' || buff[sz-1] == '\n') --sz;
    // cut them off:
	buff[sz] = '\0';
	return (ssize_t)sz;
}

ssize_t query(int fd, const char * const cmd, size_t cmdsize, char * const buff, size_t buffsize) {
	if (send(fd, cmd, cmdsize) > 0) {
		return receive(fd, buff, buffsize);
	} else return 0;
}