// Студенты, текстовый файл

#include <stdlib.h>

#include "errors.h"
#include "argch.h"
#include "studsort.h"
#include "studfprint.h"
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

    // filein fileout substr
    if (key_code == FORM_CODE)
        err_code = stud_fprint(argv[2], argv[3], argv[4]);

    if (key_code == DEL_CODE)
        err_code = stud_delete(argv[2]);

    //show_err(err_code);

    return err_code;
}
