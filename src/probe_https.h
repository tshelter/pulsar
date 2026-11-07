#ifndef PULSAR_PROBE_HTTPS_H
#define PULSAR_PROBE_HTTPS_H

#include "core.h"

int pulsar_probe_https_init(const pulsar_target_t *t);
int pulsar_probe_https_run(const pulsar_target_t *t, pulsar_sample_t *out);

#endif
