/** Сортировка: пузырьком
* Тип данных: int
* Направление упорядочивания: по возрастанию
*/

#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fbin.h"

#define MAX_PATH 260
#define ARG_COUNT 3

int main(int argc, char *argv[])
{
    if (argc != ARG_COUNT)
        return ERR_ARGS;

    int err_code = EXIT_SUCCESS;
    int not_c_key = strcmp(argv[1], "c");
    int not_p_key = strcmp(argv[1], "p");
    int not_s_key = strcmp(argv[1], "s");

    if (not_c_key && not_p_key && not_s_key)
        err_code = ERR_ARGS;
    else if (strlen(argv[2]) > MAX_PATH)
        return ERR_PATH;

    if (!not_c_key)
        return fmake_bin(argv[2]);
   
    if (!not_p_key)
        return fprint_bin(argv[2]);
    
    if (!not_s_key)
        return fsort_bin(argv[2]);

    return err_code;
}
