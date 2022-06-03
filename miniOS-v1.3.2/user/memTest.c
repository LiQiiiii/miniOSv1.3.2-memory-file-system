#include "stdio.h"

int main(int arg, char *argv[])
{
    int i = 10;
    //printf("test1:\n");
    char buf[20] = "nwpuos";
    int fd = open("orange1/test.txt", O_CREAT | O_RDWR);
    printf("fd:%d\n", fd);
    char dist[20] = "";
    int len = write(fd, buf, 10);
    printf("write:%s\n", buf);
    close(fd);
    fd = open("orange1/test.txt", O_RDWR);
    // fd = do_vopen(str, O_CREAT | O_RDWR);
    read(fd, dist, len);
    dist[len] = '\0';
    close(fd);
    printf("read:%s\n", dist);

    while (1)
    {
    };
}