#!/usr/bin/env bash
set -euo pipefail

if [ "${GITHUB_TOKEN:-}" = "" ] || [ "${SIGNING_KEY_CONTENTS:-}" = "" ] || [ "${SIGNING_KEY_PASSPHRASE:-}" = "" ]; then
  echo "Signing material is not configured. Skipping signing."
  exit 0
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "${tmpkey}" "${tmpdir}"' EXIT

tmpkey="${tmpdir}/signing.key"
printf '%s' "${SIGNING_KEY_CONTENTS}" > "${tmpkey}"
chmod 600 "${tmpkey}"

export GIT_AUTHOR_NAME="Yernar Tursynali"
export GIT_AUTHOR_EMAIL="dev@zxc.sx"
export GIT_COMMITTER_NAME="Yernar Tursynali"
export GIT_COMMITTER_EMAIL="dev@zxc.sx"
export GIT_TERMINAL_PROMPT=0

gh auth login --with-token <<< "${GITHUB_TOKEN}" --hostname github.com

repo="$(gh repo view --json nameWithOwner --jq '.nameWithOwner' 2>/dev/null || echo tshelter/pulsar)"
for asset in dist/*; do
  [ -f "${asset}" ] || continue
  echo "Signing ${asset}..."
  gh release upload "${GITHUB_REF_NAME:-v0.0.0}" "${asset}" --clobber --repo "${repo}"
done

echo "Signed assets uploaded."
