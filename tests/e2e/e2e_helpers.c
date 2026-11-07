/* e2e_helpers.c - tc qdisc helpers for loopback loss/error injection */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define CMD_BUF 4096

static int run_cmd(const char *cmd)
{
    int rc = system(cmd);
    if (rc == -1) {
        fprintf(stderr, "e2e: cannot run: %s\n", cmd);
        return -1;
    }
    if (WIFEXITED(rc)) {
        return WEXITSTATUS(rc);
    }
    fprintf(stderr, "e2e: command terminated abnormally: %s\n", cmd);
    return -1;
}

int e2e_tc_clean(const char *dev)
{
    char buf[CMD_BUF];
    if (!dev) return -1;
    snprintf(buf, sizeof(buf), "tc qdisc del dev %s root 2>/dev/null || true", dev);
    return run_cmd(buf);
}

int e2e_tc_loss(const char *dev, const char *handle, int percent)
{
    char buf[CMD_BUF];
    if (!dev || !handle) return -1;
    if (percent < 0 || percent > 100) return -1;
    snprintf(buf, sizeof(buf),
             "tc qdisc add dev %s root handle %s netem loss %d%% 2>/dev/null", dev, handle, percent);
    return run_cmd(buf);
}

int e2e_tc_delay(const char *dev, const char *handle, const char *delay)
{
    char buf[CMD_BUF];
    if (!dev || !handle || !delay) return -1;
    snprintf(buf, sizeof(buf),
             "tc qdisc add dev %s root handle %s netem delay %s 2>/dev/null", dev, handle, delay);
    return run_cmd(buf);
}

int e2e_tc_corrupt(const char *dev, const char *handle)
{
    char buf[CMD_BUF];
    if (!dev || !handle) return -1;
    snprintf(buf, sizeof(buf),
             "tc qdisc add dev %s root handle %s netem corrupt 2>/dev/null", dev, handle);
    return run_cmd(buf);
}
