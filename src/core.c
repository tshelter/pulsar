#include "core.h"
#include <string.h>

int pulsar_stats_init(pulsar_stats_t *s)
{
    if (!s) return -1;
    memset(s, 0, sizeof(*s));
    s->min_us = -1;
    s->prev_us = -1;
    s->last_us = -1;
    return 0;
}

int pulsar_stats_update(pulsar_stats_t *s, const pulsar_sample_t *samp)
{
    if (!s || !samp) return -1;
    s->sent++;
    if (samp->result == PULSAR_OK) {
        int us = samp->rtt_us;
        if (us < 0) us = 0;
        s->sum_us += (uint64_t)us;
        if (s->min_us < 0 || us < s->min_us) s->min_us = us;
        if (us > s->max_us) s->max_us = us;
        s->last_us = us;
        if (s->prev_us >= 0) {
            int d = us - s->prev_us;
            if (d < 0) d = -d;
        }
        s->prev_us = us;
    } else {
        s->lost++;
        s->last_us = -1;
    }
    return 0;
}

int pulsar_stats_loss_rate(pulsar_stats_t *s, int *num, int *den)
{
    if (!s || !num || !den) return -1;
    *num = (int)s->lost;
    *den = (int)s->sent;
    return 0;
}
