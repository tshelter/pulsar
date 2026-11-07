#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "core.h"
#include "probe_http.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

static void test_http_init_null(void)
{
    check(pulsar_probe_http_init(NULL) == -1, "http init rejects null");
}

static void test_http_run_null(void)
{
    check(pulsar_probe_http_run(NULL, NULL) == -1, "http run rejects all null");
    check(pulsar_probe_http_run(NULL, &(pulsar_sample_t){0}) == -1, "http run rejects null target");
    pulsar_target_t t = {0};
    check(pulsar_probe_http_run(&t, NULL) == -1, "http run rejects null sample");
}

static void test_http_life_cycle(void)
{
    tests_run = 0;
    tests_ok = 0;
    pulsar_target_t t = {
        .name = "http-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 80,
        .proto = PROTO_HTTP,
    };
    int r = pulsar_probe_http_init(&t);
    check(r == 0, "http init ok");
    pulsar_sample_t samp;
    r = pulsar_probe_http_run(&t, &samp);
    check(r == 0, "http run ok after init");
    check(samp.result == PULSAR_OK, "http sample ok");
    check(samp.rtt_us == 10000, "http sample rtt");
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    test_http_init_null();
    test_http_run_null();
    test_http_life_cycle();

    printf("http tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
