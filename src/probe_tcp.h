#ifndef PULSAR_PROBE_TCP_H
#define PULSAR_PROBE_TCP_H

#include "core.h"

int pulsar_probe_tcp_init(const pulsar_target_t *t);
int pulsar_probe_tcp_run(const pulsar_target_t *t, pulsar_sample_t *out);

#endif
