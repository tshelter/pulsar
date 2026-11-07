CC       ?= gcc
CFLAGS   ?= -std=c11 -Wall -Wextra -O2
LDFLAGS  ?= -static-libgcc
TARGET   = pulsar
VERSION  = $(shell sed -n 's/^#define PULSAR_VERSION "\([^"]*\)"/\1/p' ../src/core.h)

SRCS = main.c core.c probe_dns.c
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
	@echo "$(VERSION)"
