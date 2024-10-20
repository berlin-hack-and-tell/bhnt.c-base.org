#!/bin/sh
set -o xtrace

# get submodules (reveal.js)
git submodule init
git pull --recurse-submodules

# run local jekyll server; will be served at http://localhost:4000
# latest version from https://github.com/github/pages-gem/releases
export GITHUB_PAGES_GEM_VERSION=v232
docker run --rm \
  --volume="$PWD:/src/site" -p 4000:4000 \
  --env JEKYLL_UID=$(id -u) --env JEKYLL_GID=$(id -g) \
  -it ghcr.io/github/pages-gem:$GITHUB_PAGES_GEM_VERSION \
  jekyll serve --host 0.0.0.0 --future --drafts --watch --force_polling --incremental
