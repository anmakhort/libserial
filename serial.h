#ifndef SERIAL_H
#define SERIAL_H

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define DEFLT_BUFF_SZ	64
#define CMD(str)		str"\r\n"
#define CMD_N_SZ(size)	(size+2)
#define CMD_S_SZ(str)	strlen(str+2)

#define SPEED_0			B0
#define SPEED_1			B50
#define SPEED_2			B75
#define SPEED_3			B110
#define SPEED_4			B134
#define SPEED_5			B150
#define SPEED_6			B200
#define SPEED_7			B300
#define SPEED_8			B600
#define SPEED_9			B1200
#define SPEED_10		B1800
#define SPEED_11		B2400
#define SPEED_12		B4800
#define SPEED_13		B9600
#define SPEED_14		B19200
#define SPEED_15		B38400
#define SPEED_16		B57600
#define SPEED_17		B115200
#define SPEED_18		B230400

#define DEFAULT_SPEED	SPEED_13

#define FUNCT_ATTR		__attribute__((always_inline)) inline


FUNCT_ATTR int set_iface_attribs(int fd, int speed, int parity);
FUNCT_ATTR int set_blocking_mode(int fd, int block);

int init_device(const char * const path, int speed);

ssize_t send(int fd, const char * const cmd, ssize_t size);
ssize_t receive(int fd, char * const buff, size_t size);
ssize_t query(int fd, const char * const cmd, size_t cmdsize, char * const buff, size_t buffsize);

#endif