#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STR_MAX_LEN 257
#define WORD_MAX_LEN 17
#define WORD_MAX_COUNT 128

#define ERROR_INPUT 1
#define ERROR_WORD 2
#define ERROR_ASCII 3
#define ERROR_EMPTY 4

#define TRUE 1
#define FALSE 0

char *strip_str(char *const str)
{
    char *end = str + strlen(str) - 1;
    char *begin = str;

    while ((end >= str) && (isspace(*end)))
        end--;

    *(end + 1) = '\0';

    while ((*begin) && (isspace(*begin)))
        begin++;

    return begin;
}

int get_string(char *const str, const size_t max_size)
{
    char *error_p = fgets(str, max_size, stdin);

    if ((error_p == NULL) || (str[strlen(str) - 1] != '\n'))
        return ERROR_INPUT;

    return EXIT_SUCCESS;
}

// Проверка на соответствие строки рег. выр.: 
// ([eE][+-]?\d+)
int is_exppart(char *const str, char *const end)
{
    char *beg = str;

    if (beg > end)
        return TRUE;

    if ((*beg != 'e') && (*beg != 'E'))
        return FALSE;

    beg = beg + 1;

    if (beg > end)
        return FALSE;

    if ((*beg == '+') || (*beg == '-'))
        beg = beg + 1;

    int has_digit = 0;

    while (beg <= end)
    {
        if (!isdigit(*beg))
            return FALSE;
        else
            has_digit = 1;

        beg = beg + 1;
    }

    if (!has_digit)
        return FALSE;

    return TRUE;
}

int is_float_numb(char *const str)
{
    if (strlen(str) == 0)
        return FALSE;

    if ((strlen(str) == 1) && (!isdigit(str[0])))
        return FALSE;

    size_t i = 0;
    char correct_first[] = "0123456789.-+";

    if (strchr(correct_first, str[i]) == NULL)
        return FALSE;

    if ((str[i] == '+') || (str[i] == '-'))
        i++;

    int has_dot = 0;

    if (str[i] == '.')
    {
        i++;
        has_dot = 1;
    }

    int has_digit = 0;

    while (isdigit(str[i]))
    {
        has_digit = 1;
        i++;
    }

    if ((str[i] == '.') && (!has_dot))
    {
        i++;

        while (isdigit(str[i]))
        {
            i++;
            has_digit = 1;
        }
    }

    if (!has_digit)
        return FALSE;

    if (is_exppart(str + i, str + strlen(str) - 1))
        return TRUE;

    return FALSE;
}

void print_result(const int cond)
{
    if (cond)
        printf("%s\n", "YES");
    else
        printf("%s\n", "NO");
}

int main(void)
{
    char str[STR_MAX_LEN] = "";
    int input_error = get_string(str, STR_MAX_LEN - 1);

    if (input_error != EXIT_SUCCESS)
        return input_error;

    char *strp = strip_str(str);

    print_result(is_float_numb(strp));

    return EXIT_SUCCESS;
}
