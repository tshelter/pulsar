#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "core.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    pulsar_stats_t s;
    check(pulsar_stats_init(&s) == 0, "stats init ok in main tests");
    check(s.sent == 0, "stats init sent zero");

    printf("main tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
