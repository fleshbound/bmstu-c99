// Студенты, текстовый файл

#include <stdlib.h>

#include "errors.h"
#include "argch.h"
#include "studsort.h"
#include "studmatch.h"
#include "studdelete.h"

int main(int argc, char *argv[])
{
    int err_args = check_argc(argc);

    if (err_args)
        return err_args;

    int key_code = NO_CODE;
    err_args = check_argv(argc, argv, &key_code);

    if (err_args)
        return err_args;

    if (key_code == SORT_CODE)
        return sort_students(argv[2]);

    // Входной файл, выходной файл, подстрока
    if (key_code == MATCH_CODE)
        return show_students(argv[2], argv[3], argv[4]);

    if (key_code == DEL_CODE)
        return delete_students(argv[2]);

    return EXIT_SUCCESS;
}
