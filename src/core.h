#ifndef PULSAR_CORE_H
#define PULSAR_CORE_H

#include <stddef.h>
#include <stdint.h>

#define PULSAR_VERSION "0.0.2-dev"

typedef enum {
    PROTO_ICMP = 1,
    PROTO_DNS,
    PROTO_TCP,
    PROTO_UDP,
    PROTO_HTTP,
    PROTO_HTTPS,
} pulsar_proto_t;

typedef struct {
    const char *name;
    const char *host;     /* may be hostname or IP */
    int af;               /* AF_INET or AF_INET6 */
    uint16_t port;
    pulsar_proto_t proto;
} pulsar_target_t;

typedef enum {
    PULSAR_OK = 0,
    PULSAR_LOSS,
    PULSAR_ERROR,
} pulsar_result_t;

typedef struct {
    uint64_t ts_us;
    int rtt_us;
    pulsar_result_t result;
} pulsar_sample_t;

typedef struct {
    uint64_t sent;
    uint64_t lost;
    int64_t min_us;
    int64_t max_us;
    uint64_t sum_us;
    int last_us;
    int prev_us;
} pulsar_stats_t;

typedef int (*pulsar_probe_fn)(const pulsar_target_t *t, pulsar_sample_t *out);

int pulsar_stats_init(pulsar_stats_t *s);
int pulsar_stats_update(pulsar_stats_t *s, const pulsar_sample_t *samp);
int pulsar_stats_loss_rate(pulsar_stats_t *s, int *num, int *den);

#endif
