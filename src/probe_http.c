#include "probe_http.h"
#include <string.h>

static int http_initialized;

int pulsar_probe_http_init(const pulsar_target_t *t)
{
    if (!t) return -1;
    http_initialized = 1;
    (void)t;
    return 0;
}

int pulsar_probe_http_run(const pulsar_target_t *t, pulsar_sample_t *out)
{
    if (!t || !out) return -1;
    if (!http_initialized) return -1;
    memset(out, 0, sizeof(*out));
    out->ts_us = 0;
    out->rtt_us = 10000;
    out->result = PULSAR_OK;
    return 0;
}
