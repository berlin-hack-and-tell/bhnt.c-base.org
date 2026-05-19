#!/bin/sh
set -Cefu

echo 'Creating Python venv if needed ...'
[ -e .venv ] || python3 -m venv .venv

. .venv/bin/activate

echo 'Installing and updating Python packages as needed ...'
python3 -m ensurepip --upgrade
python3 -m pip install -r requirements.txt

exec python3 copy-announcement.py
