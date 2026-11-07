# PULSAR

PULSAR is a small native C project for active target probing. v0.1.0 ships the CLI core and
stages a cross-platform GUI idea, with each OS using its own native UI toolkit.

CLI: small native C CLI first.

GUI: small native GUI first, best UX CLI too. The GUI idea is shared across platforms; the pixel
implementation is native per OS.

## What v0.1.0 is

- CLI core with DNS, ICMP, UDP, HTTP, HTTPS, TCP probes.
- Signed GitHub releases, with GitHub builds in CD signed.
- Staged GUI area: macOS AppKit prototype, Linux native-toolkit prototype, shared core sketch.

## Signed releases

Signed GitHub releases are wired and enabled. GitHub builds in CD are signed.

## Releases

Use tagged release branches. Create and push a tag to trigger the release workflow.

## High level directions

1. Finish CLI core: all probe sources, tests, Nix build, version.
2. Stage the GUI area: prototypes and shared core sketch, not finished backends.
3. Cut signed releases from the planned increments.
4. Continue toward real native probe cores per platform.

## Build

From the repo root:

- CLI: `make -C src clean && make -C src`
- Version: `make -C src version`
- Tests: `make -C tests clean && make -C tests && make -C tests run`
- Nix: `nix build .`

## GUI area

See `gui/` for the staged GUI area, prototypes, and plans.

## Where this comes from

PULSAR carries forward the DNS Ping idea as the Windows design reference. Other platform GUIs keep
the same idea, implemented with each OS native UI toolkit.
