#include <assert.h>
#include "unit_tests.h"

int test_fill(int *data, my_matrix_t *test, const size_t rows, const size_t cols)
{
    *test = test_alloc(rows, cols);

    if (test->data == NULL)
        return EXIT_FAILURE;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            test->data[i][j] = data[i * cols + j];

    return EXIT_SUCCESS;
}

void test_free(my_matrix_t test)
{
    for (size_t i = 0; i < test.rows; i++)
        free(test.data[i]);

    free(test.data);
}

my_matrix_t test_alloc(const size_t rows, const size_t cols)
{
    my_matrix_t tmp = { .rows = rows, .cols = cols, .data = NULL };
    tmp.data = calloc(rows, sizeof(int *));

    if (tmp.data != NULL)
        for (size_t i = 0; i < rows; i++)
        {
            tmp.data[i] = calloc(cols, sizeof(int));
        
            if (tmp.data[i] == NULL)
                test_free(tmp);
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
