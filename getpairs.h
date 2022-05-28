#ifndef __GETP_H__

#define __GETP_H__

#define WORD_LEN 15 + 1
#define ERR_IO 2
#define PAIRS_COUNT 50 * 2
#define WORDS_COUNT 50

typedef struct pair
{
    char first_word[WORD_LEN];
    char second_word[WORD_LEN];
} word_pair;

int show_pairs(char *const file_in, char *const file_out);

#endif
