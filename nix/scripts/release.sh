#!/usr/bin/env bash
set -euo pipefail

version="${VERSION:-$(make -C src version 2>/dev/null | sed -n 's/^0\.[0-9.]*$/&/p' | tr -d '[:space:]')}"

target="${TARGET:-x86_64-linux}"
artifact="pulsar-${target}-${version}"

if [ ! -f "result/bin/pulsar" ]; then
  echo "ERROR: result/bin/pulsar not found. Run nix build . first."
  exit 1
fi

mkdir -p dist
cp "result/bin/pulsar" "dist/${artifact}"
chmod 755 "dist/${artifact}"

if [ "${SIGNING_KEY_CONTENTS:-}" != "" ] && [ "${SIGNING_KEY_PASSPHRASE:-}" != "" ] && [ "${GITHUB_TOKEN:-}" != "" ]; then
  tmpdir="$(mktemp -d)"
  trap 'rm -rf "${tmpdir}"' EXIT

  keyfile="${tmpdir}/signing.key"
  printf '%s' "${SIGNING_KEY_CONTENTS}" > "${keyfile}"
  chmod 600 "${keyfile}"

  GNUPGHOME="${tmpdir}/gnupg"
  export GNUPGHOME
  mkdir -p "${GNUPGHOME}"
  chmod 700 "${GNUPGHOME}"

  gpg --batch --yes --no-tty --pinentry-mode loopback \
    --passphrase "${SIGNING_KEY_PASSPHRASE}" \
    --import "${keyfile}" >/dev/null 2>&1

  gpg --batch --yes --no-tty --pinentry-mode loopback \
    --passphrase "${SIGNING_KEY_PASSPHRASE}" \
    --armor --detach-sign --output "dist/${artifact}.asc" "dist/${artifact}"

  gh auth login --with-token <<< "${GITHUB_TOKEN}" --hostname github.com

  repo="$(gh repo view --json nameWithOwner --jq '.nameWithOwner' 2>/dev/null || echo tshelter/pulsar)"
  gh release upload "${version}" "dist/${artifact}" "dist/${artifact}.asc" --clobber --repo "${repo}"

  echo "Signed and uploaded ${artifact} and ${artifact}.asc"
else
  echo "Signing material not configured. Prepared artifact ${artifact} but not signed/uploaded."
  exit 0
fi
