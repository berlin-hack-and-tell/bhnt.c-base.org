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
file_name="${local_date}-no${bhnt_no}-${file_title}.md"
post_file="_posts/${file_name}"
slides_file="_slides/${file_name}"

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

Upcoming - please [RSVP here](https://www.meetup.com/de-DE/berlin-hack-and-tell/events/${event_id})

EOF
echo '#############################################################################'
echo "Generating ${slides_file} ..."
echo '#############################################################################'

tee "${slides_file}" <<EOF
---
layout: slides
title: Berlin Hack & Tell \\#${bhnt_no} - ${bhnt_title}
date: ${local_date}
time: '${local_time}'
description: Slides for BHNT \\#${bhnt_no}
---


<section data-markdown>
## BHNT \\#${bhnt_no} - ${bhnt_title}

![](/assets/images/${bhnt_no}/logo.png)

We start 1923 *sharpIsh*
</section>

<section>
<h2>Sequence</h2>

<ol start="0">
  <li>Intro (this)</li>
  <li>Constraints</li>
  <li>Warmup</li>
  <li>Slots 0..3</li>
  <li>Open(ish) Mic</li>
  <li>Break</li>
  <li>Slots 4..7</li>
  <li>Vote/Trophy</li>
</ol>

</section>

<section>
<h2>Constraints</h2>

<ol start="0">
  <li>Be excellent to each other</li>
  <li>Do not smoke</li>
  <li>Respect the 5min</li>
  <li>Should be your thing</li>
  <li>NO PURE SLIDEDECKS</li>
  <li>No pitches</li>
  <li>No business</li>
  <li>Edutain us!</li>
</ol>
</section>

<section data-markdown>
## &#9812;
<center>
KEEP CALM</br>
AND</br>
KEEP YOUR</br>
PHONES IN</br>
SILENT MODE</br>
</center>
</section>

<section data-markdown>
## Local Infrastructure:
* wifi
 * SSID: c-base-public
 * pw: hacktheplanet
* emergency exits
* consume
 * bar
 * replicators
* waste collection
</section>

<section data-markdown>
## Global Infrastructure:
* www: https://bhnt.c-base.org
* md: https://md.c-base.org/bhnt-${bhnt_no}
* matrix: #bhnt:c-base.org
* HashTag: #BHNT${bhnt_no}
* BlueSky: bhnt.c-base.org
* Mastodon: https://chaos.social/@BHNT
* X: https://twitter.com/BerlinHacknTell
</section>

<section data-background-size="contain" data-background="/assets/images/trophy.jpg"></section>

<section data-background-size="contain" data-background="/assets/images/trophies.jpg"></section>

<section data-markdown>
## WarmUp
</section>

<section>
<center>
<img src="/assets/images/${bhnt_no}/logo.png"/>
</center>
</section>

<section data-markdown>
## Slots 0..3
</section>

<section data-markdown>
## Open Mic

* Stand up to speak
* Stick to 1-2 sentences
</section>

<section>
<h2>Break</h2>

<ul>
<li>Until <input style="margin-left: 0.2em; font-size: 100%; width: 4em; border: 1px solid white; background-color: transparent; color: white; text-align: center;"></li>
<li>Bottles back to the bar</li>
<li>Update your presentation details:</li>
</ul>
<center>
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=https%3A%2F%2Fmd.c-base.org%2Fbhnt-${bhnt_no}&amp;qzone=1&amp;margin=0&amp;size=300x300&amp;ecc=L" alt="QR code">
<div style="font-family: mono; font-size: 70%;">https://md.c-base.org/bhnt-${bhnt_no}</div>
</center>
</section>

<section>
<h2>Vote</h2>

<ul>
<li>wifi:c-base-public</li>
<li>pw:hacktheplanet</li>
<li>http://172.31.78.169</li>
</ul>
<center>
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=http%3A%2F%2F172.31.78.169&amp;qzone=1&amp;margin=0&amp;size=400x400&amp;ecc=L" alt="QR code">
</center>
</section>

<section>
<h2>And the winner is ...</h2>

<center>
<img src="../assets/images/trophy.jpg" alt="Trophy">
</center>
</section>

EOF
echo '#############################################################################'

echo
echo 'Done.'
echo
