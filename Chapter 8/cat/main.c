#include <fcntl.h>
#include <io.h>

#define MAX_SIZE        1024

int main(int argc, char *argv[])
{
    int fd_out, fd_in, n_bytes;
    char buffer[MAX_SIZE];

    fd_out = 1;
    if(argc == 1)
        fd_in = 0;
    else
        if((fd_in = open(argv[1], O_RDONLY)) == -1)
            write(2, "error occured", 14);

    while((n_bytes = read(fd_in, buffer, MAX_SIZE)) > 0)
        write(fd_out, buffer, n_bytes);
    return 0;
}