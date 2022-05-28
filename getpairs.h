#ifndef __GETP_H__

#define __GETP_H__

#define WORD_LEN 15 + 1

#define ERR_IO 2
#define ERR_R 3

#define PAIRS_COUNT 50 * 2
#define WORDS_COUNT 50
#define DIFF_COUNT 1

#define TRUE 1
#define FALSE 0

typedef struct pair
{
    char first_word[WORD_LEN];
    char second_word[WORD_LEN];
} word_pair;

int show_pairs(char *const file_in, char *const file_out);

#endif
