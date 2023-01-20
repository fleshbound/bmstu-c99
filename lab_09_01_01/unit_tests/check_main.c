#include <assert.h>

#include "unit_tests.h"

void free_test(info_movie_t *test)
{
    if ((*test)->title != NULL)
        free((*test)->title);

    if ((*test)->name != NULL)
        free((*test)->name);

    free(*test);
}

int main(void)
{
    size_t failed = 0;
    srunner *runner; 
    
    suite *movies_suite = get_movies_suite();
    runner = srunner_create(movies_suite);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_VERBOSE);

    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}
