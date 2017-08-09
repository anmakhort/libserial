#include "../serial.h"
#include <stdio.h>

#define HAMEG_PATH  "/dev/serial/by-id/usb-HAMEG_Instruments_HO820_019641048-if00-port0"

#define INIT_ALL                                \
    int fd = init_device(HAMEG_PATH, SPEED_15); \
    if (fd < 0) return -1;                      \
    char buff[64];

#define FREE_ALL    \
    close(fd);      \
    return 0;

#define PRINT_RESP                                      \
    buff[cnt] = '\0';                                   \
    printf("QUERIED: [%d bytes]: %s\n", (int)cnt, buff);

int main()
{
	INIT_ALL
    
    ssize_t cnt = query(fd, "*IDN?\r\n", 5+2, buff, 64);
    PRINT_RESP
    
    cnt = query(fd, "PMOD?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "VOLT?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMAJ?\r\n", 5+2, buff, 64);
    PRINT_RESP

    cnt = query(fd, "XMIN?\r\n", 5+2, buff, 64);
    PRINT_RESP
    
    FREE_ALL
}