#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "core.h"
#include "probe_https.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

static void test_https_init_null(void)
{
    check(pulsar_probe_https_init(NULL) == -1, "https init rejects null");
}

static void test_https_run_null(void)
{
    check(pulsar_probe_https_run(NULL, NULL) == -1, "https run rejects all null");
    check(pulsar_probe_https_run(NULL, &(pulsar_sample_t){0}) == -1, "https run rejects null target");
    pulsar_target_t t = {0};
    check(pulsar_probe_https_run(&t, NULL) == -1, "https run rejects null sample");
}

static void test_https_life_cycle(void)
{
    tests_run = 0;
    tests_ok = 0;
    pulsar_target_t t = {
        .name = "https-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 443,
        .proto = PROTO_HTTPS,
    };
    int r = pulsar_probe_https_init(&t);
    check(r == 0, "https init ok");
    pulsar_sample_t samp;
    r = pulsar_probe_https_run(&t, &samp);
    check(r == 0, "https run ok after init");
    check(samp.result == PULSAR_OK, "https sample ok");
    check(samp.rtt_us == 15000, "https sample rtt");
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    test_https_init_null();
    test_https_run_null();
    test_https_life_cycle();

    printf("https tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
