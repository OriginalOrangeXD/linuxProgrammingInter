#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    off_t endOfFile = lseek(fd, 0, SEEK_END);
    if (endOfFile == -1)
        errExit("lseek");
    unsigned char *buf;
    buf = malloc(endOfFile);
    if (buf == NULL)
        errExit("malloc");
    lseek(fd, 0, SEEK_SET);
    int numRead = read(fd, buf, endOfFile);
    if (numRead == -1)
        errExit("read");
    if(close(fd) == -1)
        errExit("close");
    if (numRead == 0)
        errExit("%s: end-of-file\n", argv[1]);

    fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    int wr = write(fd, buf, endOfFile);
    if (wr == -1)
        errExit("write");

    for (int i =0; i < endOfFile; i++){
        printf("%c", isprint(buf[i]) ? buf[i] : '?');
    }
    printf("\nBytes : %ld\n", endOfFile);
    free(buf);
}
