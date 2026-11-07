#include <stdio.h>
#include <stdlib.h>

#define PULSAR_VERSION "0.0.1"

static int usage(const char *prog)
{
    fprintf(stderr, "usage: %s [--version] [command]\n", prog);
    return 2;
}

int main(int argc, char **argv)
{
    if (argc > 1 && argv[1][0] == '-') {
        if (argv[1][1] == 'v' && !argv[1][2]) {
            printf("pulsar %s\n", PULSAR_VERSION);
            return 0;
        }
        return usage(argv[0]);
    }
    if (argc > 1) {
        printf("pulsar %s: command not implemented yet: %s\n", PULSAR_VERSION, argv[1]);
        return 1;
    }
    printf("pulsar %s\n", PULSAR_VERSION);
    return 0;
}
