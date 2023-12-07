# Berlin Hack & Tell

This project uses the Jekyll static site generator.

## Build (Docker)

To build and host the site locally inside a temporary Docker container, execute the following, and connect to http://localhost:4000/ .

1. `build.sh`

## Build (local)

You can also run Jekyll without Docker:

1. Install Ruby development packages and Bundler, e.g. on Debian:  `apt-get install bundler ruby-dev`
2. Install Jekyll and all required modules: `bundle install`
3. Run Jekyll: `bundle exec jekyll serve --future --drafts`
4. Open the generated site in your browser: http://localhost:4000/
