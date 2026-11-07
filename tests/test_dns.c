#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "core.h"
#include "probe_dns.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

static void test_dns_init_null(void)
{
    check(pulsar_probe_dns_init(NULL) == -1, "dns init rejects null");
}

static void test_dns_run_null(void)
{
    check(pulsar_probe_dns_run(NULL, NULL) == -1, "dns run rejects all null");
    check(pulsar_probe_dns_run(NULL, &(pulsar_sample_t){0}) == -1, "dns run rejects null target");
    pulsar_target_t t = {0};
    check(pulsar_probe_dns_run(&t, NULL) == -1, "dns run rejects null sample");
}

static void test_dns_life_cycle(void)
{
    tests_run = 0;
    tests_ok = 0;
    pulsar_target_t t = {
        .name = "dns-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 53,
        .proto = PROTO_DNS,
    };
    int r = pulsar_probe_dns_init(&t);
    check(r == 0, "dns init ok");
    pulsar_sample_t samp;
    r = pulsar_probe_dns_run(&t, &samp);
    check(r == 0, "dns run ok after init");
    check(samp.result == PULSAR_OK, "dns sample ok");
    check(samp.rtt_us == 1000, "dns sample rtt");
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    test_dns_init_null();
    test_dns_run_null();
    test_dns_life_cycle();

    printf("dns tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
