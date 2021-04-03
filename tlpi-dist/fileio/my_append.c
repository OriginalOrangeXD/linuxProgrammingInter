#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") ==0)
        usageErr("%s file {append data} \n", argv[0]);
    int fd, numWr;
    fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    numWr = write(fd, &argv[2][0], strlen(&argv[2][0]));
    if (numWr == -1)
        errExit("write");
    printf("%s: wrote %ld bytes\n", argv[2], (long) numWr);
    exit(EXIT_SUCCESS);
    return 0;
}
