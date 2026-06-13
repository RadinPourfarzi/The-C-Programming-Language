/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include "buffer.h"
#include "search.h"
#include "options.h"

int main(int argc, char *argv[])
{
    int fd, status, i;
    unsigned int lc, ln;

    read_arguments(argc, argv);
    read_flags();
    
    return 0;
}