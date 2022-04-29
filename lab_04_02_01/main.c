#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN_MAX 256
#define WORD_MAX_LEN 16
#define WORD_MAX_COUNT 128
#define ERROR_INPUT 1
#define ERROR_WORD 2

int is_first_bigger(char *const str1, char *const str2)
{
    size_t min_len = (strlen(str1) > strlen(str2)) ? strlen(str2) : strlen(str1);

    for (size_t i = 0; i < min_len; i++)
        if (str1[i] > str2[i])
            return 1;

    if (strlen(str1) > strlen(str2))
        return 1;

    return 0;
}

void swap_words(char *wrd1, char *wrd2)
{
    char *max_wrd = (strlen(wrd1) > strlen(wrd2)) ? wrd1 : wrd2;
    char *min_wrd = (strlen(wrd1) > strlen(wrd2)) ? wrd2 : wrd1;
    size_t max_len = strlen(max_wrd);

    for (size_t i = 0; i < max_len; i++)
    {
        char buf = max_wrd[i];
        max_wrd[i] = min_wrd[i];
        min_wrd[i] = buf;
    }
}

void sort_words(char words[][WORD_MAX_LEN], const size_t size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = size - 1; j > i - 1; j--)
            if (is_first_bigger(words[j - 1], words[j]))
                swap_words(words[j - 1], words[j]);
}

int get_words(char *const str, char words[][WORD_MAX_LEN], size_t *const word_len)
{
    char curr_symb = '\0';
    size_t curr_wsize = 0, curr_word_ind = 0, curr_symb_ind = 0;

    for (size_t i = 0; i < strlen(str) + 1; i++)
    {
        if (curr_wsize == WORD_MAX_LEN)
            return ERROR_WORD;

        if (isspace(str[i]) || ispunct(str[i]))
        {
            if (curr_symb != '\0')
            {
                curr_symb = '\0';
                words[curr_word_ind][curr_symb_ind + 1] = curr_symb;
                curr_wsize = 0;
                curr_word_ind++;
                curr_symb_ind = 0;
            }
        }
        else
        {
            curr_symb = str[i];
            words[curr_word_ind][curr_symb_ind] = curr_symb;
            curr_symb_ind++;
            curr_wsize++; 
       	}
    }

    if (curr_word_ind == 0)
        return ERROR_WORD;

    *word_len = curr_word_ind;

    return EXIT_SUCCESS;
}

int get_string(char *const str, const size_t size)
{
    printf("Enter string:\n");
    char *error_p = fgets(str, size, stdin);
    
    if ((error_p == NULL) || (strlen(str) == 0))
        return ERROR_INPUT;
    
    return EXIT_SUCCESS;
}

void print_words(char words[][WORD_MAX_LEN], const size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%s%c", words[i], (i == size - 1) ? '\n' : ' ');
}

int main(void)
{
    char str[STR_LEN_MAX];
    
    int inp_error = get_string(str, STR_LEN_MAX);

    if (inp_error != EXIT_SUCCESS)
        return inp_error;

    char words[WORD_MAX_COUNT][WORD_MAX_LEN] = { "" };
    size_t words_count = 0;
    int word_error = get_words(str, words, &words_count);

    if (word_error != EXIT_SUCCESS)
        return word_error;

    sort_words(words, words_count);
    printf("Result: ");
    print_words(words, words_count);
    
    return EXIT_SUCCESS;
}
