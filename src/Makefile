CC       ?= gcc
CFLAGS   ?= -std=c11 -Wall -Wextra -O2
LDFLAGS  ?= -static-libgcc
TARGET   = pulsar
VERSION  := $(shell grep '^#define PULSAR_VERSION' ../src/core.h | sed -n 's/.*"\(.*\)".*/\1/p')

SRCS = main.c core.c probe_dns.c probe_tcp.c probe_icmp.c probe_udp.c probe_http.c probe_https.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: version
version:
	@echo $(VERSION)
