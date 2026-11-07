#ifndef PULSAR_PROBE_HTTP_H
#define PULSAR_PROBE_HTTP_H

#include "core.h"

int pulsar_probe_http_init(const pulsar_target_t *t);
int pulsar_probe_http_run(const pulsar_target_t *t, pulsar_sample_t *out);

#endif
