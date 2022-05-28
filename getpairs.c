#include <stdio.h>
#include <stdlib.h>

#include "getpairs.h"

int get_words(f, *words)
{
    if (fgets())
}

void get_pairs(word_pair pairs[PAIRS_COUNT], FILE *const f)
{
    char *words[WORDS_COUNT] = { "" };

    while ((!feof(f)) && (!err_code))
        
}

int show_pairs(char *const in_file, char *const file_out)
{
    FILE *f_in = fopen(in_file, "rt");

    if (f_in == NULL)
        return ERR_IO;

    word_pair pairs[PAIRS_COUNT];

    get_pairs(pairs, f_in);
    
    fclose(f_in);
    
    analyze_pairs(pairs);

    FILE *f_out = fopen(file_out, "wt");

    if (f_out == NULL)
        return ERR_IO;

    print_pairs(pairs, f_out);

    fclose(f_out);

    return EXIT_SUCCESS;
}
