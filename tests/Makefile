CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2
TESTS = test_core test_main test_dns test_tcp test_icmp test_udp test_http test_https
SRCS = test_core.c test_main.c test_dns.c test_tcp.c test_icmp.c test_udp.c test_http.c test_https.c ../src/core.c ../src/probe_dns.c ../src/probe_tcp.c ../src/probe_icmp.c ../src/probe_udp.c ../src/probe_http.c ../src/probe_https.c

.PHONY: all clean run

all: $(TESTS)

$(TESTS): %: %.o ../src/core.o ../src/probe_dns.o ../src/probe_tcp.o ../src/probe_icmp.o ../src/probe_udp.o ../src/probe_http.o ../src/probe_https.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/core.o: ../src/core.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_dns.o: ../src/probe_dns.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_tcp.o: ../src/probe_tcp.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_icmp.o: ../src/probe_icmp.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_udp.o: ../src/probe_udp.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_http.o: ../src/probe_http.c
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

../src/probe_https.o: ../src/probe_https.c
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
