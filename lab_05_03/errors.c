#include <stdio.h>

#include "errors.h"

void show_err(const int code)
{
    if (code == ERR_EMPTY)
        printf("Error: File is empty\n");

    if (code == ERR_WRITE)
        printf("Error while writing in file\n");

    if (code == ERR_IO)
        printf("I/O error\n");

    if (code == ERR_ARGS)
        printf("Error: Invalid command line arguments\n");

    if (code == ERR_READ)
        printf("Error while reading file\n");

    if (code == ERR_DATA)
        printf("File consists of invalid data (only ints were excepted)\n");
}
