#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"


int main(int argc, char *argv[]){
    int fd;
    fd = open(argv[1], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    if( fd == -1)
        errExit("open");

    if(lseek(fd, 0, SEEK_SET) == -1)
        errExit("lseek");

    if(write(fd, "x", 1) == -1)
        fatal("write() failed");

    printf("%ld done\n", (long) getpid());
    exit(EXIT_SUCCESS);
}
