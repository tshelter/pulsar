CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TESTS = test_core test_main
SRCS = test_core.c test_main.c ../src/core.c

.PHONY: all clean run

all: $(TESTS)

$(TESTS): %: %.o ../src/core.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/core.o: ../src/core.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

run: $(TESTS)
	@ failure=0; \
	for t in $(TESTS); do \
		echo "--- $$t ---"; \
		./$$t || failure=1; \
	done; \
	exit $$failure

clean:
	rm -f $(SRCS:.c=.o) $(TESTS)
