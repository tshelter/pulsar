#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "core.h"
#include "pulsar.h"
#include "probe_dns.h"

static void print_version(void)
{
    printf("pulsar %s\n", PULSAR_VERSION);
}

static int cmd_version(void)
{
    print_version();
    return 0;
}

static int cmd_version_main(int argc, char **argv)
{
    (void)argv;
    return cmd_version();
}

static int cmd_help(void)
{
    fprintf(stdout, "usage: pulsar [--version] [command]\n\ncommands:\n  version\n  help\n");
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

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }
    if (argc > 1 && strcmp(argv[1], "version") == 0)
        return cmd_version_main(argc - 1, argv + 1);
    if (argc > 1 && strcmp(argv[1], "help") == 0)
        return cmd_help();
    if (argc > 1 && strcmp(argv[1], "dns-init") == 0)
        return cmd_dns_init();
    if (argc > 1 && strcmp(argv[1], "dns-run") == 0)
        return cmd_dns_run();
    if (argc > 1) {
        fprintf(stderr, "pulsar: unknown command: %s\n", argv[1]);
        return 1;
    }
    print_version();
    return 0;
}
