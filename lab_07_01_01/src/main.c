#include <stdio.h>
#include <stdlib.h>

#include "../inc/argch.h"
#include "../inc/process.h"

int main(int argc, char *argv[])
{
    int mode_code = NO_CODE, err_code = EXIT_SUCCESS;

    err_code = check_args(argc, argv, &mode_code);

    if (err_code)
        return err_code;

    // app.exe file_in file_out [f]
    err_code = fsort_file(argv[1], argv[2], mode_code);

    if (err_code)
        return err_code;

    return err_code;
}
