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
int GetP_TZeroEmpty_NotNull(void)
{
    char symbol = '\0';
    char str[STR_MAX_LEN] = "";
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения терминирующего нуля в непустой строке
int GetP_TZeroNEmpty_NotNull(void)
{
    char symbol = '\0';
    char str[STR_MAX_LEN] = "abc";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа, который отсутствует
int GetP_SymNonEmpty_Null(void)
{
    char symbol = '1';
    char str[STR_MAX_LEN] = "2345";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа, который присутствует
int GetP_SymNonEmpty_NotNull(void)
{   
    char symbol = '1';
    char str[STR_MAX_LEN] = "21345";
    int count_failed = 0;
    return (is_equal_strchr(str, symbol) + is_equal_strrchr(str, symbol));
}

// Проверка положения символа из второй строки (обе пустые)
int GetP_SymEmptyEmpty_Null(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    int count_failed = 0;
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй непустой строки в пустой
int GetP_SymNEmptyEmpty_Null(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "01";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй пустой строки
int GetP_SymEmptyNEmpty_Null(void)
{
    char str1[STR_MAX_LEN] = "012345";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй строки (отсуствует)
int GetP_SymNonEmpty_Null(void)
{
    char str1[STR_MAX_LEN] = "012345";
    char str2[STR_MAX_LEN] = "78";
    return is_equal_strpbrk(str1, str2);
}

// Проверка положения символа из второй строки (присутствует)
int GetP_SymNonEmpty_NotNull(void)
{
    char str1[STR_MAX_LEN] = "7890123";
    char str2[STR_MAX_LEN] = "02";
    return is_equal_strpbrk(str1, str2);
}

// Длина символов пустой в пустой
int GetL_EmptyInEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strspn(str1, str2);
}

// Длина символов пустой в непустой
int GetL_EmptyInNonEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "01234";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в пустой
int GetL_NonEmptyInEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в непустой (отсутствуют)
int GetL_NonEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "7895";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

// Длина символов непустой в непустой (присутствуют)
int GetL_NonEmpty_NotZero(void)
{
    char str1[STR_MAX_LEN] = "42130878";
    char str2[STR_MAX_LEN] = "01234";
    return is_equal_strspn(str1, str2);
}

int GetLB_SymEmptyEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strcspn(str1, str2);
}

int GetLB_SymEmptyNonEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "13224";
    char str2[STR_MAX_LEN] = "";
    return is_equal_strcspn(str1, str2);
}

int GetLB_SymNonEmptyEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "";
    char str2[STR_MAX_LEN] = "324234";
    return is_equal_strcspn(str1, str2);
}

int GetLB_SymNonEmpty_Zero(void)
{
    char str1[STR_MAX_LEN] = "123456";
    char str2[STR_MAX_LEN] = "zxcvb";
    return is_equal_strcspn(str1, str2);
}

int GetLB_SymNonEmpty_NotZero(void)
{
    char str1[STR_MAX_LEN] = "abcdf";
    char str2[STR_MAX_LEN] = "f324";
    return is_equal_strcspn(str1, str2);
}

int test_strpbrk(void)
{
    int count_failed = 0;
    count_failed = count_failed + GetP_SymEmptyEmpty_Null();
    count_failed = count_failed + GetP_SymNEmptyEmpty_Null();
    count_failed = count_failed + GetP_SymEmptyNEmpty_Null();
    count_failed = count_failed + GetP_SymNonEmpty_Null();
    count_failed = count_failed + GetP_SymNonEmpty_NotNull();
    return count_failed;
}

int test_strspn(void)
{
    int count_failed = 0;
    count_failed = count_failed + GetL_EmptyInEmpty_Zero();
    count_failed = count_failed + GetL_EmptyInNonEmpty_Zero();
    count_failed = count_failed + GetL_NonEmptyInEmpty_Zero();
    count_failed = count_failed + GetL_NonEmpty_Zero();
    count_failed = count_failed + GetL_NonEmpty_NotZero();
    return count_failed;
}

int test_strcspn(void)
{
    int count_failed = 0;
    count_failed = count_failed + GetLB_SymEmptyEmpty_Zero();
    count_failed = count_failed + GetLB_SymEmptyNonEmpty_Zero();    
    count_failed = count_failed + GetLB_SymNonEmptyEmpty_Zero();    
    count_failed = count_failed + GetLB_SymNonEmpty_Zero();    
    count_failed = count_failed + GetLB_SymNonEmpty_NotZero();    
    return count_failed;
}

int test_strchr_strrchr(void)
{
    int count_failed = 0;
    count_failed = count_failed + GetP_TZeroEmpty_NotNull();
    count_failed = count_failed + GetP_TZeroNEmpty_NotNull();
    count_failed = count_failed + GetP_SymNonEmpty_Null();
    count_failed = count_failed + GetP_SymNonEmpty_NotNull();
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
