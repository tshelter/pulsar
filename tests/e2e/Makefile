CC       ?= gcc
CFLAGS   ?= -std=c11 -Wall -Wextra -O2
TARGET   = pulsar-e2e
SRCS     = e2e_helpers.c e2e_runner.c

.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I. -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

help:
	@echo "e2e targets: all, clean, run, help"

clean:
	rm -f $(SRCS:.c=.o) $(TARGET)
