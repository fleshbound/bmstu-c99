#ifndef _FUNC_H_
#define _FUNC_H_

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "polynom.h"

#define NO_CODE 0
#define CODE_VAL 1
#define CODE_DDX 2
#define CODE_SUM 3
#define CODE_DVD 4

#define COMMAND_LEN 3

#define STR_VAL "val"
#define STR_DDX "ddx"
#define STR_SUM "sum"
#define STR_DVD "dvd"

int get_func_code_by_user(int *const code);
int func_by_code(const int code);

#endif
