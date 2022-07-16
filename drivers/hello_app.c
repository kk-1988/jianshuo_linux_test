#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>

#define DATA_NUM (64)
int main(int argc, char *argv[])
{
    int fd,i;
    int r_len, w_len;
    char buf[DATA_NUM] = "hello world";
    memset(buf, 0, DATA_NUM);
    fd = open("/dev/hello", O_RDWR);
    printf("%d\r\n", fd);
    if(-1 == fd)
    {
        perror("open file error\r\n");
        return -1;
    }
    else
    {
        printf("open success\r\n");
    }

    w_len = write(fd, buf, DATA_NUM);
    if(w_len == -1)
    {
        perror("write error\n");
        return -1;
    }
    sleep(5);
    printf("write len:%d\r\n", w_len);
    close(fd);
    return 0;
}