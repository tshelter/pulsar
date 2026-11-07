#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "core.h"

static int tests_run;
static int tests_ok;

static void check(int cond, const char *msg)
{
    tests_run++;
    if (cond) tests_ok++;
    else fprintf(stderr, "FAIL: %s\n", msg);
}

static void test_stats_init(void)
{
    pulsar_stats_t s;
    int r = pulsar_stats_init(&s);
    check(r == 0, "stats init returns 0");
    check(s.sent == 0 && s.lost == 0, "stats zeroed");
    check(s.min_us == -1 && s.prev_us == -1 && s.last_us == -1, "stats sentinels");
}

static void test_stats_update_ok(void)
{
    pulsar_stats_t s;
    pulsar_sample_t samp;
    pulsar_stats_init(&s);
    samp.ts_us = 1;
    samp.result = PULSAR_OK;
    samp.rtt_us = 5000;
    check(pulsar_stats_update(&s, &samp) == 0, "update ok returns 0");
    check(s.sent == 1 && s.lost == 0, "sent 1 after ok");
    check(s.min_us == 5000 && s.max_us == 5000, "min/max set");
    check(s.sum_us == 5000, "sum correct");

    samp.rtt_us = 3000;
    pulsar_stats_update(&s, &samp);
    check(s.min_us == 3000 && s.max_us == 5000, "min/max updated");
    check(s.sum_us == 8000, "sum updated");
}

static void test_stats_update_loss(void)
{
    pulsar_stats_t s;
    pulsar_sample_t samp;
    pulsar_stats_init(&s);
    samp.ts_us = 1;
    samp.result = PULSAR_LOSS;
    samp.rtt_us = -1;
    check(pulsar_stats_update(&s, &samp) == 0, "update loss returns 0");
    check(s.sent == 1 && s.lost == 1, "loss counted");
    check(s.min_us == -1 && s.max_us == 0, "min/max unchanged for loss");
}

static void test_stats_loss_rate(void)
{
    pulsar_stats_t s;
    int num, den;
    pulsar_stats_init(&s);
    check(pulsar_stats_loss_rate(&s, &num, &den) == 0, "loss rate callable");
    check(num == 0 && den == 0, "initial rate zero");

    s.sent = 5;
    s.lost = 2;
    check(pulsar_stats_loss_rate(&s, &num, &den) == 0, "loss rate callable after state");
    check(num == 2 && den == 5, "loss rate numbers match");
}

static void test_bad_args(void)
{
    check(pulsar_stats_init(NULL) == -1, "init rejects null");
    pulsar_stats_t s;
    pulsar_sample_t samp;
    memset(&samp, 0, sizeof(samp));
    check(pulsar_stats_update(NULL, &samp) == -1, "update rejects null stats");
    check(pulsar_stats_update(&s, NULL) == -1, "update rejects null sample");
    int num, den;
    check(pulsar_stats_loss_rate(NULL, &num, &den) == -1, "loss rate rejects null stats");
    check(pulsar_stats_loss_rate(&s, NULL, &den) == -1, "loss rate rejects null num");
    check(pulsar_stats_loss_rate(&s, &num, NULL) == -1, "loss rate rejects null den");
}

int main(void)
{
    tests_run = 0;
    tests_ok = 0;

    test_stats_init();
    test_stats_update_ok();
    test_stats_update_loss();
    test_stats_loss_rate();
    test_bad_args();

    printf("core tests: %d/%d passed\n", tests_ok, tests_run);
    return tests_ok == tests_run ? 0 : 1;
}
