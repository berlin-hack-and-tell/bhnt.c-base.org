#!/bin/sh

# get submodules (reveal.js)
git submodule init
git pull --recurse-submodules

# run local jekyll server; will be served at localhost:8080
export JEKYLL_VERSION=3.8
docker run --rm \
  --volume="$PWD:/srv/jekyll" -p 8080:4000 \
  -it jekyll/jekyll:$JEKYLL_VERSION \
  jekyll serve

