/* file not_so_simpler.c */
 
#include <stdio.h>

#include "minunit.h"
#include "adder.c"
 
int tests_run = 0;
char tmb_buffer[128];
 
static char * test_add() {
    int a = 10;
    int b = 20;

    int result = adder(a,b);
    int expected = a + b;

    sprintf(tmb_buffer, "test_add: %d != %d", expected, result);

    mu_assert(tmb_buffer, result == expected);
    return 0;
}

static char * test_subtract() {
    int a = 10;
    int b = -20;

    int result = adder(a,b);
    int expected = a + b;

    sprintf(tmb_buffer, "test_subtract: %d != %d", expected, result);

    mu_assert(tmb_buffer, result == expected);
    return 0;
}
 
static char * test_wrong() {
    int a = 10;
    int b = 20;

    int result = adder(a,b) + 1; // Intentional Error
    int expected = a + b;

    sprintf(tmb_buffer, "test_wrong: %d != %d", expected, result);

    mu_assert(tmb_buffer, result == expected);
    return 0;
}
 
static char * testSuite() {
    mu_run_test(test_add);
    mu_run_test(test_subtract);
    mu_run_test(test_wrong);
    return 0;
}
 
int main(int argc, char **argv) {
    printf("Verificación de la función 'adder'\n");

    char *result = testSuite();

    if (result != 0)
        printf("%s\n", result);

    else
        printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);
 
    return result != 0;
}
