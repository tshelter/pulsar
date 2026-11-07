#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "core.h"
#include "probe_icmp.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

static void test_icmp_init_null(void)
{
    check(pulsar_probe_icmp_init(NULL) == -1, "icmp init rejects null");
}

static void test_icmp_run_null(void)
{
    check(pulsar_probe_icmp_run(NULL, NULL) == -1, "icmp run rejects all null");
    check(pulsar_probe_icmp_run(NULL, &(pulsar_sample_t){0}) == -1, "icmp run rejects null target");
    pulsar_target_t t = {0};
    check(pulsar_probe_icmp_run(&t, NULL) == -1, "icmp run rejects null sample");
}

static void test_icmp_life_cycle(void)
{
    tests_run = 0;
    tests_ok = 0;
    pulsar_target_t t = {
        .name = "icmp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 0,
        .proto = PROTO_ICMP,
    };
    int r = pulsar_probe_icmp_init(&t);
    check(r == 0, "icmp init ok");
    pulsar_sample_t samp;
    r = pulsar_probe_icmp_run(&t, &samp);
    check(r == 0, "icmp run ok after init");
    check(samp.result == PULSAR_OK, "icmp sample ok");
    check(samp.rtt_us == 2000, "icmp sample rtt");
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    test_icmp_init_null();
    test_icmp_run_null();
    test_icmp_life_cycle();

    printf("icmp tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
