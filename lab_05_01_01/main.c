#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "errors.h"

void print_result(const int res_max_1, const int res_max_2)
{
    printf("Result: %d %d\n", res_max_1, res_max_2);
}

int main(void)
{
    int res_max_1, res_max_2;
    int err_proc = process(stdin, &res_max_1, &res_max_2);

    if (err_proc)
        return err_proc;

    print_result(res_max_1, res_max_2);

    return EXIT_SUCCESS;
}
