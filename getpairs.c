#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getpairs.h"

void mycpy(char *const w1, char *const w2, const size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        char buf = w2[i];
        
        if (w2[i] == '\n')
            buf = '\0';
        
        w1[i] = buf;
    }
}

void get_words(FILE *const f, char words[WORDS_COUNT][WORD_LEN], size_t *const wc)
{
    rewind(f);

    int i = 0;

    while (!feof(f))
    {
        char buf[WORD_LEN] = "";

        fgets(buf, WORD_LEN, f);// == NULL)
            //printf("");//OUCH\n");

        if ((buf[0] != '\n') && (buf[0] != '\0'))
            mycpy(words[i++], buf, WORD_LEN);
    }
    
    *wc = i;
}

int is_pair(char *const word1, char *const word2)
{
    size_t diff_q = 0;

    for (size_t i = 0; i < WORD_LEN; i++)
    {
        if (word1[i] != word2[i])
            diff_q++;
        
        if (diff_q > DIFF_COUNT)
            return FALSE;
    }

    if (diff_q != DIFF_COUNT)
        return FALSE;

    return TRUE;
}

void get_pairs(char words[][WORD_LEN], word_pair pairs[PAIRS_COUNT], size_t *const count, const size_t wc)
{
    size_t sc = 0;

    for (size_t i = 0; i < wc; i++)
        for (size_t j = i + 1; j < wc; j++)
        {
            //printf("%s, %s, %d\n", words[i], words[j], is_pair(words[i], words[j]));

            if (is_pair(words[i], words[j]))
            {
                mycpy(pairs[sc].first_word, words[i], WORD_LEN);
                mycpy(pairs[sc++].second_word, words[j], WORD_LEN);
            }
        }
    
    *count = sc;
}

void print_pairs(word_pair pairs[PAIRS_COUNT], const size_t count, FILE *const f)
{
    for (size_t i = 0; i < count; i++)
        fprintf(f, "%s, %s\n", pairs[i].first_word, pairs[i].second_word);
}
    
int show_pairs(char *const in_file, char *const file_out)
{
    FILE *f_in = fopen(in_file, "rt");

    if (f_in == NULL)
        return ERR_IO;

    word_pair pairs[PAIRS_COUNT];
    char words[WORDS_COUNT][WORD_LEN];
    size_t pairsc = 0, wc = 0;

    get_words(f_in, words, &wc);
    get_pairs(words, pairs, &pairsc, wc);
    
    fclose(f_in);

    FILE *f_out = fopen(file_out, "wt");

    if (f_out == NULL)
        return ERR_IO;

    print_pairs(pairs, pairsc, f_out);

    fclose(f_out);

    return EXIT_SUCCESS;
}
