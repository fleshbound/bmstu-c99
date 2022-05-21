// Сортировка пузырьком, тип int, упорядочивание по возрастанию

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fbin.h"

#define MAX_PATH 260
#define ARG_COUNT 3

int main(int argc, char *argv[])
{
    if (argc != ARG_COUNT)
    {
        show_err(ERR_ARGS);
        return ERR_ARGS;
    }

    int err_code = EXIT_SUCCESS;
    int not_c_key = strcmp(argv[1], "c");
    int not_p_key = strcmp(argv[1], "p");
    int not_s_key = strcmp(argv[1], "s");

    if (not_c_key && not_p_key && not_s_key)
        err_code = ERR_ARGS;
    else if (strlen(argv[2]) > MAX_PATH)
    {
        show_err(ERR_PATH);
        return ERR_PATH;
    }

    if (!not_c_key)
        err_code = fmake_bin(argv[2]);
   
    if (!not_p_key)
        err_code = fprint_bin(argv[2]);
    
    if (!not_s_key)
        err_code = fsort_bin(argv[2]);

    show_err(err_code);

    return err_code;
}
