#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX_LEN 256

// Указатель на первый элемент str1, равный элементу из str2 (без нулевых символов)
char * my_strpbrk(const char *str1, const char *str2)
{
    char *result_p = NULL;
    
    for (size_t i = 0; (i < strlen(str1)) && (result_p == NULL); i++)
        for (size_t j = 0; (j < strlen(str2)) && (result_p == NULL); j++)
            if (str1[i] == str2[j])
                result_p = (char *)str1 + i;

    return result_p;
}

// Длина начального участка str1, содержащего только символы str2
size_t my_strspn(const char *str1, const char *str2)
{
    size_t result = 0;

    for (size_t i = 0; (i < strlen(str1)) && (result == i); i++)
        for (size_t j = 0; (j < strlen(str2)) && (result == i); j++)
            if (str1[i] == str2[j])
                result++;

    return result;
}

// Количество символов в str1 до певрого найденного символа str2
size_t my_strcspn(const char *str1, const char *str2)
{
    for (size_t i = 0; (i < strlen(str1) + 1); i++)
        for (size_t j = 0; (j < strlen(str2) + 1); j++)
            if (str1[i] == str2[j])
                return i;

    return strlen(str1);
}

// Указатель на первое вхождение указанного символа (с нулевыми символами)
char * my_strchr(const char *str, int symbol)
{
    char *result_p = NULL;

    for (size_t i = 0; (i < strlen(str) + 1) && (result_p == NULL); i++)
    {
        char curr_symb = symbol;

        if (str[i] == curr_symb)
            result_p = (char *)str + i;
    }

    return result_p;
}

// Указатель на последнее вхождение указанного символа (с нулевыми символами)
char * my_strrchr(const char *str, int symbol)
{
    char *result_p = NULL;

    for (int i = strlen(str); (i > -1) && (result_p == NULL); i--)
    {
        char curr_symb = symbol;

        if (str[i] == curr_symb)
            result_p = (char *)str + i;
    }

    return result_p;
}

// Сравнение результатов strpbrk
int is_equal_strpbrk(const char *str1, const char *str2)
{
    return !(my_strpbrk(str1, str2) == strpbrk(str1, str2));
}

// Сравнение результатов strspn
int is_equal_strspn(const char *str1, const char *str2)
{
    return !(my_strspn(str1, str2) == strspn(str1, str2));
}

// Сравнение результатов strcspn
int is_equal_strcspn(const char *str1, const char *str2)
{
    return !(my_strcspn(str1, str2) == strcspn(str1, str2));
}

// Сравнение результатов strchr
int is_equal_strchr(const char *str, int symbol)
{
    return !(my_strchr(str, symbol) == strchr(str, symbol));
}

// Сравнение результатов strrchr
int is_equal_strrchr(const char *str, int symbol)
{
    return !(my_strrchr(str, symbol) == strrchr(str, symbol));
}

// Проверка положения терминирующего нуля в пустой строке
int getp_Tzeroempty_notnull(void)
{
    char symbol = '\0';
    char str[STR_MAX_LEN] = "";
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения терминирующего нуля в непустой строке
int getp_Tzeronempty_notnull(void)
{
    char symbol = '\0';
    char str[STR_MAX_LEN] = "abc";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа, который отсутствует
int getp_symnonempty_n(void)
{
    char symbol = '1';
    char str[STR_MAX_LEN] = "2345";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа, который присутствует
int getp_symnonempty_notnull(void)
{   
    char symbol = '1';
    char str[STR_MAX_LEN] = "21345";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа из второй строки (обе пустые)
int getp_symemptyempty_n(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    int count_failed = 0;
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй непустой строки в пустой
int getp_symnemptyempty_n(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "01";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй пустой строки
int getp_symemptynempty_n(void)
{
    char str1[STR_MAX_LEN] = "012345";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй строки (отсуствует)
int getp_strnonempty_n(void)
{
    char str1[STR_MAX_LEN] = "012345";
    char str2[STR_MAX_LEN] = "78";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй строки (присутствует)
int getp_strnonempty_notnull(void)
{
    char str1[STR_MAX_LEN] = "7890123";
    char str2[STR_MAX_LEN] = "02";
    return is_equal_strpbrk(str1, str2);
}

// Длина символов пустой в пустой
int getl_emptyinempty_zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strspn(str1, str2);
}

// Длина символов пустой в непустой
int getl_emptyinnonempty_zero(void)
{
    char str1[STR_MAX_LEN] = "01234";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в пустой
int getl_nonemptyinempty_zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в непустой (отсутствуют)
int getl_nonempty_zero(void)
{
    char str1[STR_MAX_LEN] = "7895";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в непустой (присутствуют)
int getl_nonempty_notzero(void)
{
    char str1[STR_MAX_LEN] = "42130878";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

int getlb_symemptyempty_zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strcspn(str1, str2);
}

int getlb_symemptynonempty_zero(void)
{
    char str1[STR_MAX_LEN] = "13224";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strcspn(str1, str2);
}

int getlb_symnonemptyempty_zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "324234";
    return is_equal_strcspn(str1, str2);
}

int getlb_symnonempty_zero(void)
{
    char str1[STR_MAX_LEN] = "123456";
    char str2[STR_MAX_LEN] = "zxcvb";
    return is_equal_strcspn(str1, str2);
}

int getlb_symnonempty_notzero(void)
{
    char str1[STR_MAX_LEN] = "abcdf";
    char str2[STR_MAX_LEN] = "f324";
    return is_equal_strcspn(str1, str2);
}

int test_strpbrk(void)
{
    int count_failed = 0;
    count_failed = count_failed + getp_symemptyempty_null();
    count_failed = count_failed + getp_symnemptyempty_null();
    count_failed = count_failed + getp_symemptynempty_null();
    count_failed = count_failed + getp_strnonempty_null();
    count_failed = count_failed + getp_strnonempty_notnull();
    return count_failed;
}

int test_strspn(void)
{
    int count_failed = 0;
    count_failed = count_failed + getl_emptyinempty_zero();
    count_failed = count_failed + getl_emptyinnonempty_zero();
    count_failed = count_failed + getl_nonemptyinempty_zero();
    count_failed = count_failed + getl_nonempty_zero();
    count_failed = count_failed + getl_nonempty_notzero();
    return count_failed;
}

int test_strcspn(void)
{
    int count_failed = 0;
    count_failed = count_failed + getlb_symemptyempty_zero();
    count_failed = count_failed + getlb_symemptynonempty_zero();    
    count_failed = count_failed + getlb_symnonemptyempty_zero();    
    count_failed = count_failed + getlb_symnonempty_zero();    
    count_failed = count_failed + getlb_symnonempty_notzero();    
    return count_failed;
}

int test_strchr_strrchr(void)
{
    int count_failed = 0;
    count_failed = count_failed + getp_Tzeroempty_notnull();
    count_failed = count_failed + getp_Tzeronempty_notnull();
    count_failed = count_failed + getp_symnonempty_null();
    count_failed = count_failed + getp_symnonempty_notnull();
    return count_failed;
}

int unit_testing(void)
{
    int total_count_failed = 0;
    total_count_failed = total_count_failed + test_strpbrk();
    total_count_failed = total_count_failed + test_strspn();
    total_count_failed = total_count_failed + test_strcspn();
    total_count_failed = total_count_failed + test_strchr_strrchr();
    return total_count_failed;
}

int main(void)
{
    int total_failures = unit_testing();

    printf("%d\n", total_failures);

    return EXIT_SUCCESS;
}
