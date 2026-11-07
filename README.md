# PULSAR

Multi-protocol Internet Connectivity Observatory.

Priority order:

- small native C CLI first
- Nix build and dev shell
- signed GitHub builds in CI/CD
- Linux e2e tests with `tc`
- unit tests toward 100% coverage

## Build

```bash
nix build .
./result/bin/pulsar --version
```

## Tests

```bash
make -C tests clean
make -C tests
make -C tests run
```

## e2e harness

See `tests/e2e/README.md` for the Linux `tc` harness notes.

## Signing

Signed releases are wired but disabled until signing material is provided.

See `nix/scripts/release.sh` and `.github/workflows/release.yml`.
