#!/bin/sh

# get submodules (reveal.js)
git submodule init
git pull --recurse-submodules

# run local jekyll server; will be served at localhost:4000
export JEKYLL_VERSION=3.8
docker run --rm \
  --volume="$PWD:/srv/jekyll" -p 4000:4000 \
  --env JEKYLL_UID=$(id -u) --env JEKYLL_GID=$(id -g) \
  -it jekyll/jekyll:$JEKYLL_VERSION \
  jekyll serve --future --drafts
