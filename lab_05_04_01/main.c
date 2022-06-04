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

    int err_code = EXIT_SUCCESS;

    if (key_code == SORT_CODE)
        err_code = stud_sort(argv[2]);

    // Входной файл, выходной файл, подстрока
    if (key_code == MATCH_CODE)
        err_code = show_stud_matches(argv[2], argv[3], argv[4]);

    if (key_code == DEL_CODE)
        err_code = stud_delete(argv[2]);

    return err_code;
}
