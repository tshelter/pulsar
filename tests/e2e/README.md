# Pulsar e2e harness

This directory is a Linux-only e2e harness for `pulsar`.

## What it does

- Provides tc qdisc helpers for loopback loss, delay, and corruption.
- Is intended to be wired to `pulsar` CLI/run commands later.
- Does not pretend to be a cross-platform network test framework.

## Requirements

- Linux
- root or appropriate capabilities to modify `lo`
- `tc` from iproute2
- `ip` helpful for interface checks

## Constraints

Right now the harness targets loopback only. This machine cannot create
network namespaces as a normal user, so namespace-based isolation is not
part of this first cut.

## Build

```bash
make -C tests/e2e
```

## Run

```bash
make -C tests/e2e run
```

## Clean

```bash
make -C tests/e2e clean
```
