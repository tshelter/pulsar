PULSAR Release Plan

- [x] Stand up pulsar repo and flake-based dev shell + first commit scaffolding
- [x] Define v0.0.1 scope and release plan (basic CLI + portable build + first release)
- [x] v0.0.1: OS-native C core, small, portable build (Linux/Mac/Windows via Nix), first release
- [x] v0.0.2: target/connectivity core with ICMP + DNS probes, unit tests begin
- [ ] v0.0.3: additional probes (TCP, HTTP/S, UDP echo), unit tests, CLI commands
- [ ] v0.0.N: CI/CD pipeline, signed builds, release automation, e2e/chaos tests with tc
- [ ] v0.1.0: final release from planned increments, verify builds + tests + releases

Notes:
- Signed builds via Nix are desired for GitHub Actions releases.
- Linux "super static super portable" is a key target.
- Final goal: v0.1.0 with full coverage roadmap and tc-based e2e tests.
