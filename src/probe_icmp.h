#ifndef PULSAR_PROBE_ICMP_H
#define PULSAR_PROBE_ICMP_H

#include "core.h"

int pulsar_probe_icmp_init(const pulsar_target_t *t);
int pulsar_probe_icmp_run(const pulsar_target_t *t, pulsar_sample_t *out);

#endif
