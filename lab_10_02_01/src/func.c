#include "func.h"

int get_func_code_by_user(int *const code)
{
    char *command = NULL;
    size_t len = 0;

    if (getline(&command, &len, stdin) == -1)
        return EXIT_FAILURE;

    if (!strncmp(command, STR_VAL, COMMAND_LEN))
        *code = CODE_VAL;
    
    if (!strncmp(command, STR_DDX, COMMAND_LEN))
        *code = CODE_DDX;
    
    if (!strncmp(command, STR_SUM, COMMAND_LEN))
        *code = CODE_SUM;

    if (!strncmp(command, STR_DVD, COMMAND_LEN))
        *code = CODE_DVD;

    free(command);

    if (*code == NO_CODE)
        return ERR_COMMAND;

    return EXIT_SUCCESS;
}

int func_list_val(void)
{
    list_t polynom;
    int arg;
    int rc = input_arg_polynom(&polynom, &arg);

    if (rc)
    {
        fprintf(stderr, "ERROR: %d\n", rc);
        return rc;
    }

    /* print_polynom(polynom); */
    /* printf("Arg: %d\n", arg); */

    printf("%d\n", calc_polynom(polynom, arg));
    free_polynom(&polynom);

    return EXIT_SUCCESS;
}

int func_list_ddx(void)
{
    list_t polynom;
    int rc = input_polynom(&polynom);

    if (rc)
    {
        fprintf(stderr, "ERROR: %d\n", rc);
        return rc;
    }

    list_t new_polynom = get_ddx_polynom(polynom);
    
    if (new_polynom == NULL)
        return EXIT_FAILURE;

    print_polynom(new_polynom);
    free_polynom(&polynom);
    free_polynom(&new_polynom);

    return EXIT_SUCCESS;
}

int func_list_sum(void)
{
    list_t polynom_a;
    int rc = input_polynom(&polynom_a);

    if (rc)
    {
        fprintf(stderr, "ERROR: %d\n", rc);
        return rc;
    }

    list_t polynom_b;
    rc = input_polynom(&polynom_b);

    if (rc)
    {
        fprintf(stderr, "ERROR: %d\n", rc);
        return rc;
    }

    list_t sum_polynom = sum_polynoms(&polynom_a, &polynom_b);
    
    if (sum_polynom == NULL)
        return ERR_MEM;

    print_polynom(sum_polynom);
    free_polynom(&sum_polynom);

    return EXIT_SUCCESS;
}

int func_list_dvd(void)
{
    list_t polynom;
    int rc = input_polynom(&polynom);

    if (rc)
    {
        fprintf(stderr, "ERROR: %d\n", rc);
        return rc;
    }

    list_t even_polynom = NULL, odd_polynom = NULL;

    get_odd_even_poly(polynom, &even_polynom, &odd_polynom);
    
    print_polynom(even_polynom);
    print_polynom(odd_polynom);

    free_polynom(&even_polynom);
    free_polynom(&odd_polynom);

    return EXIT_SUCCESS;
}

int func_by_code(const int code)
{
    if (code == CODE_VAL)
        return func_list_val();

    if (code == CODE_DDX)
        return func_list_ddx();

    if (code == CODE_SUM)
        return func_list_sum();

    return func_list_dvd();
}
