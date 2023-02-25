#!/bin/sh
set -eu

echo 'Fetching list of events ...'
event_list_json=$(curl -#f "https://api.meetup.com/berlin-hack-and-tell/")
event_id=$(echo "${event_list_json}" | sed -n 's/^.*"next_event":{[^}]*"id":"\([^"]*\)".*$/\1/p')
echo 'Fetching upcoming event ...'
event_json=$(curl -#f "https://api.meetup.com/berlin-hack-and-tell/events/${event_id}/")
local_date=$(echo "${event_json}" | sed -n 's/^.*"local_date":"\([^"]*\)".*$/\1/p')
local_time=$(echo "${event_json}" | sed -n 's/^.*"local_time":"\([^"]*\)".*$/\1/p')
name=$(echo "${event_json}" | sed -n 's/{[^{]*"name":"\([^"]*\)".*$/\1/p')
bhnt_no=$(echo "${name}" | sed -n 's/^[^#]*#\([0-9]\+\).*$/\1/p')
bhnt_title=$(echo "${name}" | sed -n 's/^\(.*[^ ]\) * - BHNT .*$/\1/p')
file_title=$(echo "${bhnt_title}" | tr A-Z a-z | sed 's/[^0-9a-z]/-/g')
post_file="_posts/${local_date}-no${bhnt_no}-${file_title}.md"

echo
echo "Generating ${post_file} ..."
echo '#############################################################################'

tee "${post_file}" <<EOF
---
layout: post
title: Berlin Hack & Tell \\#${bhnt_no} - ${bhnt_title}
date: ${local_date}
published: true
time: '${local_time}'
location: '[c-base](https://www.c-base.org)'
meetupUrl: https://www.meetup.com/de-DE/berlin-hack-and-tell/events/${event_id}
---

Upcoming
EOF
echo '#############################################################################'

echo
echo 'Done.'
echo
