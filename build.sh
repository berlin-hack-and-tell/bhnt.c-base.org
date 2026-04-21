#!/bin/sh
set -o xtrace

# get submodules (reveal.js)
git submodule init
git pull --recurse-submodules

JEKYLL_COMMAND="jekyll serve --host 0.0.0.0 --future --drafts --watch --force_polling"
# if 'full' is passed, don't add '--incremental'` flag
# use this if you encounter rendering issues (e.g. missing posts on the homepage)
if [ "$1" != "full" ]; then
  JEKYLL_COMMAND="$JEKYLL_COMMAND --incremental"
fi

# run local jekyll server; will be served at http://localhost:4000
# latest version from https://github.com/github/pages-gem/releases
export GITHUB_PAGES_GEM_VERSION=v232
docker run --rm \
  --volume="$PWD:/src/site" -p 4000:4000 \
  --env JEKYLL_UID=$(id -u) --env JEKYLL_GID=$(id -g) \
  -it ghcr.io/github/pages-gem:$GITHUB_PAGES_GEM_VERSION \
  sh -c "$JEKYLL_COMMAND"
