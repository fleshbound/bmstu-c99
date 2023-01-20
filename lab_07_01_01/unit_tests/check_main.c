#include "../inc/unit_tests.h"

int main(void)
{
    size_t count_failed = 0;

    srunner *runner;

    suite *filter_suite = get_filter_suite();
    suite *sort_suite = get_sort_suite();

    runner = srunner_create(filter_suite);
    srunner_add_suite(runner, sort_suite);

    srunner_run_all(runner, CK_VERBOSE);
    count_failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    
    return (count_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
