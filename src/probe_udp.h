#ifndef PULSAR_PROBE_UDP_H
#define PULSAR_PROBE_UDP_H

#include "core.h"

int pulsar_probe_udp_init(const pulsar_target_t *t);
int pulsar_probe_udp_run(const pulsar_target_t *t, pulsar_sample_t *out);

#endif
