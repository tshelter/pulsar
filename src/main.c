#include <stdio.h>
#include <string.h>
#include "core.h"
#include "pulsar.h"

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
    if (argc > 1) {
        fprintf(stderr, "pulsar: unknown command: %s\n", argv[1]);
        return 1;
    }
    print_version();
    return 0;
}
