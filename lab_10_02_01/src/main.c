#include <stdio.h>
#include <stdlib.h>

#include "func.h"

int main(void)
{
    int func_code = NO_CODE;
    int rc = get_func_code_by_user(&func_code);

    if (rc)
        return rc;

    return func_by_code(func_code);
}
