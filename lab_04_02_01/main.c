#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 257
#define WORD_LEN 17
#define WORD_MAX_COUNT 128

#define ERROR_INPUT 1
#define ERROR_WORD 2
#define ERROR_ASCII 3

#define TRUE 1
#define FALSE 0

int is_first_bigger(char *const str1, char *const str2)
{
    size_t i = 0;

    while ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
        i++;

    // Вторая строка совпадает с частью первой
    if ((str1[i] != '\0') && (str2[i] == '\0'))
        return TRUE;

    // Первая строка совпадает с частью второй
    if ((str1[i] == '\0') && (str2[i] != '\0'))
        return FALSE;

    // Строки равны
    if ((str1[i] == '\0') && (str2[i] == '\0'))
        return FALSE;

    if (str1[i] > str2[i])
        return TRUE;
    
    return FALSE;
}

void swap_symbs(char *wrd1, char *wrd2, const size_t ind)
{
    char buf = wrd1[ind];
    wrd1[ind] = wrd2[ind];
    wrd2[ind] = buf;
}

void swap_words(char *wrd1, char *wrd2)
{
    char *max_wrd = (strlen(wrd1) > strlen(wrd2)) ? wrd1 : wrd2;
    char *min_wrd = (strlen(wrd1) > strlen(wrd2)) ? wrd2 : wrd1;
    size_t max_len = strlen(max_wrd);

    for (size_t i = 0; i < max_len; i++)
        swap_symbs(max_wrd, min_wrd, i);
}

void sort_words(char words[][WORD_LEN], const size_t size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = size - 1; j > i - 1; j--)
            if (is_first_bigger(words[j - 1], words[j]))
                swap_words(words[j - 1], words[j]);
}

int is_equal_words(char *const wrd1, char *const wrd2)
{
    if (strlen(wrd1) != strlen(wrd2))
        return FALSE;

    for (size_t i = 0; i < strlen(wrd1); i++)
        if (wrd1[i] != wrd2[i])
            return FALSE;

    return TRUE;
}

int is_in_array(char words[][WORD_LEN], const size_t size, char *const wrd)
{
    for (size_t i = 0; i < size; i++)
        if (is_equal_words(wrd, words[i]))
            return TRUE;

    return FALSE;
}

void add_word(char words[][WORD_LEN], char *const wrd, const size_t index)
{
    for (size_t i = 0; i < strlen(wrd) + 1; i++)
        words[index][i] = wrd[i];
}

void add_checked(char words[][WORD_LEN], size_t *const w_ind, char *const wrd)
{
    if (!is_in_array(words, *w_ind + 1, wrd))
    {
        add_word(words, wrd, *w_ind);
        *w_ind = *w_ind + 1;
    }
}

int get_words(char *const str, char words[][WORD_LEN], size_t *const word_len)
{
    char curr_symb = '0';
    char curr_word[WORD_LEN] = "";
    size_t curr_wsize = 0, curr_word_ind = 0, curr_symb_ind = 0;

    for (size_t i = 0; i < strlen(str) + 1; i++)
    {
        if (curr_wsize == WORD_LEN - 1)
            return ERROR_WORD;

        if (isspace(str[i]) || ispunct(str[i]))
        {
            if (curr_symb != '\0')
            {
                curr_symb = '\0';
                curr_word[curr_symb_ind] = curr_symb;

                add_checked(words, &curr_word_ind, curr_word);

                curr_wsize = 0;
                curr_symb_ind = 0;
                curr_word[0] = '\0';
            }
        }
        else
        {
            curr_symb = str[i];
            curr_word[curr_symb_ind] = curr_symb;
            curr_symb_ind++;
            curr_wsize++;
        }
    }

    if (curr_word_ind == 0)
        return ERROR_WORD;

    *word_len = curr_word_ind;

    return EXIT_SUCCESS;
}

int is_ascii_str(char *const str)
{
    for (size_t i = 0; i < strlen(str) - 1; i++)
        if (!isprint(str[i]))
            return 0;

    return 1;
}

int get_string(char *const str, const size_t size)
{
    printf("Enter string:\n");
    char *error_p = fgets(str, size, stdin);
    
    if ((error_p == NULL) || (strlen(str) == 0) || (str[strlen(str) - 1] != '\n'))
        return ERROR_INPUT;

    if (!is_ascii_str(str))
        return ERROR_ASCII;
    
    return EXIT_SUCCESS;
}

void print_words(char words[][WORD_LEN], const size_t size)
{
    printf("Result: ");

    for (size_t i = 0; i < size; i++)
        printf("%s%c", words[i], (i == size - 1) ? '\n' : ' ');
}

int main(void)
{
    char str[STR_LEN];
    
    int inp_error = get_string(str, STR_LEN - 1);

    if (inp_error != EXIT_SUCCESS)
        return inp_error;

    char words[WORD_MAX_COUNT][WORD_LEN] = { "" };
    size_t words_count = 0;
    int word_error = get_words(str, words, &words_count);

    if (word_error != EXIT_SUCCESS)
        return word_error;

    sort_words(words, words_count);
    print_words(words, words_count);
    
    return EXIT_SUCCESS;
}
