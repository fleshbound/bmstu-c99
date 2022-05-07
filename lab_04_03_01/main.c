#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define STR_MAX_LEN 257
#define WORD_MAX_LEN 17
#define WORD_MAX_COUNT 128

#define ERROR_INPUT 1
#define ERROR_WORD 2
#define ERROR_ASCII 3
#define ERROR_EMPTY 4

int is_ascii_str(char *const str)
{
    for (size_t i = 0; i < strlen(str) - 1; i++)
        if (! isprint(str[i]))
            return 0;

    return 1;
}

int get_string(char *const str, const size_t size)
{
    printf("Enter string:\n");
    char *error_p = fgets(str, size, stdin);

    if ((error_p == NULL) || (strlen(str) == 0) || (str[strlen(str) - 1] != '\n'))
        return ERROR_INPUT;

    if (! is_ascii_str(str))
        return ERROR_ASCII;

    return EXIT_SUCCESS;
}

void insert_word_in_array(char words[][WORD_MAX_LEN], char *const str, const size_t index)
{
    for (size_t i = 0; i < strlen(str); i++)
        words[index][i] = str[i];

    words[index][strlen(str)] = '\0';
}

int get_words(char *const str, char words[][WORD_MAX_LEN], size_t *const w_count)
{
    char sep[] = " ,;:-.!?\n";
    char *curr_word = strtok(str, sep);
    size_t i = 0;

    while (curr_word != NULL)
    {
        if (strlen(curr_word) > WORD_MAX_LEN - 1)
            return ERROR_WORD;
        
        if (strlen(curr_word) > 0)
        {
            insert_word_in_array(words, curr_word, i);
            curr_word = strtok(NULL, sep);
            i++;
        }
    }

    *w_count = i;

    return EXIT_SUCCESS;
}

size_t add_word_in_str(char *const str, char *const word, const size_t index)
{
    for (size_t i = 0; i < strlen(word); i++)
        str[index + i] = word[i];

    str[index + strlen(word)] = ' ';

    return index + strlen(word) + 1;
}

void unique_letters_to_first(char *const new_word, char *const old_word)
{
    size_t j = 0;
    
    for (size_t i = 0; i < strlen(old_word); i++)
        if (strchr(new_word, old_word[i]) == NULL)
        {
            new_word[j] = old_word[i];
            j++;
        }

    new_word[j] = '\0';
}

void clear_word(char *const word, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        word[i] = '\0';
}

int fill_new_str(char *const new_str, char w_arr[][WORD_MAX_LEN], const size_t w_count)
{
    size_t ins_index = 0;
    char new_word[WORD_MAX_LEN] = { "" };
    
    for (int i = w_count - 2; i >= 0; i--)
        if (strcmp(w_arr[w_count - 1], w_arr[i]))
        {
            clear_word(new_word, WORD_MAX_LEN);
            unique_letters_to_first(new_word, w_arr[i]);
            ins_index = add_word_in_str(new_str, new_word, ins_index);
        }

    new_str[strlen(new_str) - 1] = '\0';
    
    if (strlen(new_str) == 0)
        return ERROR_EMPTY;

    return EXIT_SUCCESS;
}

int main(void)
{
    char str[STR_MAX_LEN] = "";
    int input_error = get_string(str, STR_MAX_LEN - 1);

    if (input_error != EXIT_SUCCESS)
        return input_error;

    char words[WORD_MAX_COUNT][WORD_MAX_LEN] = { "" };
    size_t w_count = 0;
    int words_error = get_words(str, words, &w_count);

    if (words_error != EXIT_SUCCESS)
        return words_error;

    char new_str[STR_MAX_LEN] = "";
    int fill_error = fill_new_str(new_str, words, w_count);

    if (fill_error != EXIT_SUCCESS)
        return fill_error;

    printf("Result: %s\n", new_str);

    return EXIT_SUCCESS;
}
