#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "core.h"
#include "pulsar.h"
#include "probe_dns.h"
#include "probe_tcp.h"
#include "probe_icmp.h"
#include "probe_udp.h"
#include "probe_http.h"
#include "probe_https.h"

static void print_version(void)
{
    printf("pulsar %s\n", PULSAR_VERSION);
}

static int cmd_version(void)
{
    print_version();
    return 0;
}

static int cmd_version_main(void)
{
    return cmd_version();
}

static int cmd_help(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    fprintf(stdout, "usage: pulsar [--version] [command]\n\ncommands:\n  version\n  help\n  dns-init\n  dns-run\n  tcp-init\n  tcp-run\n  icmp-init\n  icmp-run\n  udp-init\n  udp-run\n  http-init\n  http-run\n  https-init\n  https-run\n");
    return 0;
}

static int cmd_dns_init(void)
{
    pulsar_target_t t = {
        .name = "dns-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 53,
        .proto = PROTO_DNS,
    };
    int r = pulsar_probe_dns_init(&t);
    if (r == 0) printf("dns probe initialized\n");
    return r;
}

static int cmd_dns_run(void)
{
    pulsar_target_t t = {
        .name = "dns-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 53,
        .proto = PROTO_DNS,
    };
    pulsar_probe_dns_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_dns_run(&t, &samp);
    if (r == 0) printf("dns sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

static int cmd_tcp_init(void)
{
    pulsar_target_t t = {
        .name = "tcp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 80,
        .proto = PROTO_TCP,
    };
    int r = pulsar_probe_tcp_init(&t);
    if (r == 0) printf("tcp probe initialized\n");
    return r;
}

static int cmd_tcp_run(void)
{
    pulsar_target_t t = {
        .name = "tcp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 80,
        .proto = PROTO_TCP,
    };
    pulsar_probe_tcp_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_tcp_run(&t, &samp);
    if (r == 0) printf("tcp sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

static int cmd_icmp_init(void)
{
    pulsar_target_t t = {
        .name = "icmp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 0,
        .proto = PROTO_ICMP,
    };
    int r = pulsar_probe_icmp_init(&t);
    if (r == 0) printf("icmp probe initialized\n");
    return r;
}

static int cmd_icmp_run(void)
{
    pulsar_target_t t = {
        .name = "icmp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 0,
        .proto = PROTO_ICMP,
    };
    pulsar_probe_icmp_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_icmp_run(&t, &samp);
    if (r == 0) printf("icmp sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

static int cmd_udp_init(void)
{
    pulsar_target_t t = {
        .name = "udp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 53,
        .proto = PROTO_UDP,
    };
    int r = pulsar_probe_udp_init(&t);
    if (r == 0) printf("udp probe initialized\n");
    return r;
}

static int cmd_udp_run(void)
{
    pulsar_target_t t = {
        .name = "udp-test",
        .host = "127.0.0.1",
        .af = AF_INET,
        .port = 53,
        .proto = PROTO_UDP,
    };
    pulsar_probe_udp_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_udp_run(&t, &samp);
    if (r == 0) printf("udp sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

static int cmd_http_init(void)
{
    pulsar_target_t t = {
        .name = "http-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 80,
        .proto = PROTO_HTTP,
    };
    int r = pulsar_probe_http_init(&t);
    if (r == 0) printf("http probe initialized\n");
    return r;
}

static int cmd_http_run(void)
{
    pulsar_target_t t = {
        .name = "http-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 80,
        .proto = PROTO_HTTP,
    };
    pulsar_probe_http_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_http_run(&t, &samp);
    if (r == 0) printf("http sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

static int cmd_https_init(void)
{
    pulsar_target_t t = {
        .name = "https-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 443,
        .proto = PROTO_HTTPS,
    };
    int r = pulsar_probe_https_init(&t);
    if (r == 0) printf("https probe initialized\n");
    return r;
}

static int cmd_https_run(void)
{
    pulsar_target_t t = {
        .name = "https-test",
        .host = "example.com",
        .af = AF_INET,
        .port = 443,
        .proto = PROTO_HTTPS,
    };
    pulsar_probe_https_init(&t);
    pulsar_sample_t samp;
    int r = pulsar_probe_https_run(&t, &samp);
    if (r == 0) printf("https sample: rtt=%d result=%d\n", samp.rtt_us, samp.result);
    return r;
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "version") == 0)
        return cmd_version_main();
    if (argc > 1 && strcmp(argv[1], "help") == 0)
        return cmd_help(argc - 1, argv + 1);
    if (argc > 1 && strcmp(argv[1], "dns-init") == 0)
        return cmd_dns_init();
    if (argc > 1 && strcmp(argv[1], "dns-run") == 0)
        return cmd_dns_run();
    if (argc > 1 && strcmp(argv[1], "tcp-init") == 0)
        return cmd_tcp_init();
    if (argc > 1 && strcmp(argv[1], "tcp-run") == 0)
        return cmd_tcp_run();
    if (argc > 1 && strcmp(argv[1], "icmp-init") == 0)
        return cmd_icmp_init();
    if (argc > 1 && strcmp(argv[1], "icmp-run") == 0)
        return cmd_icmp_run();
    if (argc > 1 && strcmp(argv[1], "udp-init") == 0)
        return cmd_udp_init();
    if (argc > 1 && strcmp(argv[1], "udp-run") == 0)
        return cmd_udp_run();
    if (argc > 1 && strcmp(argv[1], "http-init") == 0)
        return cmd_http_init();
    if (argc > 1 && strcmp(argv[1], "http-run") == 0)
        return cmd_http_run();
    if (argc > 1 && strcmp(argv[1], "https-init") == 0)
        return cmd_https_init();
    if (argc > 1 && strcmp(argv[1], "https-run") == 0)
        return cmd_https_run();
    if (argc > 1) {
        fprintf(stderr, "pulsar: unknown command: %s\n", argv[1]);
        return 1;
    }
    print_version();
    return 0;
}
