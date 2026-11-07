#include "probe_udp.h"
#include <string.h>

static int udp_initialized;

int pulsar_probe_udp_init(const pulsar_target_t *t)
{
    if (!t) return -1;
    udp_initialized = 1;
    (void)t;
    return 0;
}

int pulsar_probe_udp_run(const pulsar_target_t *t, pulsar_sample_t *out)
{
    if (!t || !out) return -1;
    if (!udp_initialized) return -1;
    memset(out, 0, sizeof(*out));
    out->ts_us = 0;
    out->rtt_us = 3000;
    out->result = PULSAR_OK;
    return 0;
}
