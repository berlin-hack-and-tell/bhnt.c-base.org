# Berlin Hack & Tell

This project uses the Jekyll static site generator.

## Build (Docker)

To build and host the site locally inside a temporary Docker container:

1. Install Docker, e.g. on Debian:  `apt-get install docker.io`
2. Generate the container and run Jekyll within it: `./build.sh`
3. Open the generated site in your browser: http://localhost:4000/

## Build (local)

You can also run Jekyll without Docker:

For Debian/Ubuntu:

1. Install Ruby development packages and Bundler `apt-get install bundler ruby-dev`
2. Install Jekyll and all required modules: `bundle install`
3. Run Jekyll: `bundle exec jekyll serve --future --drafts`
4. Open the generated site in your browser: http://localhost:4000/

For macOS:

1. Install Homebrew (via https://brew.sh/)

2. run the following commands to install bundler

```bash
brew install ruby
echo 'export PATH="/opt/homebrew/opt/ruby/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
gem install bundler
```

3. Install Jekyll and all required modules: `bundle install`
4. Run Jekyll: `bundle exec jekyll serve --future --drafts`
5. Open the generated site in your browser: http://localhost:4000/

