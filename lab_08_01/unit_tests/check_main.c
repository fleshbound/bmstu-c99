#include <assert.h>
#include "unit_tests.h"

int test_fill(int *data, int ***test, const size_t rows, const size_t cols)
{
    *test = test_alloc(rows, cols);

    if (*test == NULL)
        return EXIT_FAILURE;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            (*test)[i][j] = data[i * cols + j];

    return EXIT_SUCCESS;
}

void test_free(int **data, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
        free(data[i]);

    free(data);
}

int **test_alloc(const size_t rows, const size_t cols)
{
    int **tmp = calloc(rows, sizeof(int *));

    if (tmp != NULL)
        for (size_t i = 0; i < rows; i++)
        {
            tmp[i] = calloc(cols, sizeof(int));
        
            if (tmp[i] == NULL)
            {
                test_free(tmp, rows);
                return NULL;
            }
        }
    
    return tmp;
}

int main(void)
{
    size_t count_failed = 0;

    srunner *runner;

    suite *matrix_suite = get_matrix_suite();

    runner = srunner_create(matrix_suite);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    count_failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    
    return (count_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
