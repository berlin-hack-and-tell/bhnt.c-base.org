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

Upcoming
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

![](/assets/images/0${bhnt_no}/)

We start 1923 *sharpIsh*
</section>

<section>
<h2>Structure</h2>

<ol start="0">
  <li>Intro (this)</li>
  <li>Rules</li>
  <li>News</li>
  <li>Slots 0..3</li>
  <li>Open Mic</li>
  <li>Break</li>
  <li>Slots 4..7</li>
  <li>Vote/Trophy</li>
</ol>

</section>

<section>
<h2>Rules</h2>

<ol start="0">
  <li>Be excellent to each other</li>
  <li>Do not smoke</li>
  <li>Respect the 5min</li>
  <li>Should be your thing</li>
  <li>NO PURE SLIDEDECKS</li>
  <li>No pitches</li>
  <li>No business</li>
  <li>Entertain us!</li>
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

<section>
<h2><a href="https://berlinhackandtell.rocks/">berlinhackandtell.rocks</a></h2>
<iframe class="stretch" data-src="https://berlinhackandtell.rocks"></iframe>
</section>

<section>
<pre>https://pad.systemli.org/p/bhnt0${bhnt_no}</pre>
<iframe name="embed_readwrite" src="https://pad.systemli.org/p/bhnt0${bhnt_no}?showControls=false&showChat=false&showLineNumbers=true&useMonospaceFont=true" width="100%" height="600" frameborder="0" class="stretch"></iframe>
</section>

<section data-markdown>
![Hack and Tell Trophy]({{ '/assets/images/trophy.jpg' | relative_url }})
</section>

<section data-markdown>
![Hack and Tell Trophies]({{ '/assets/images/trophies.jpg' | relative_url }})
</section>

<section data-markdown>
## WarmUp
</section>

<section>
<center>
<img src="/assets/images/0${bhnt_no}/"/>
</center>
</section>

<section data-markdown>
## Slots 0..3
</section>

<section data-markdown>
## Open Mic

* Line up at the stage
* Stick to 1-2 sentences
</section>


<section>
<h2>Help MiniMateLight!</h2>
Drink one bottle => Add one pixel
<canvas id="bottles" width="800" height="320" style="border:1px solid black;margin:50px"></canvas>
<script>
    // Thanks Clujio https://stackoverflow.com/a/44488640/388127 CC BY-SA 3.0
    var canvas = document.getElementById('bottles');
    var context = canvas.getContext('2d');
    var sizeX = canvas.width / 40;
    var sizeY = canvas.height / 16;
    var total = 320;
    var count = 0;
    for (var j = 0; j < 16; j++) { // rows
        for (var i = 0; i < 40; i++) { // columns
            context.beginPath();
            context.arc(sizeX * (i+0.5), sizeY * (j+0.5), sizeX / Math.PI, 0, 2 * Math.PI, false);
            context.fillStyle = total > count ? 'green' : 'red';
            context.fill();
            count++;
        }
    }
</script>
</section>

<section>
<h2>Break</h2>

<ul>
<li>Until <input style="margin-left: 0.2em; font-size: 100%; width: 4em; border: 1px solid white; background-color: transparent; color: white; text-align: center;"></li>
<li>Bottles back to the bar</li>
<li>Update your presentation details:</li>
</ul>
<center>
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=http%3A%2F%2Fpad.systemli.org%2Fp%2Fbhnt0&amp;qzone=1&amp;margin=0&amp;size=300x300&amp;ecc=L" alt="QR code">
<div style="font-family: mono; font-size: 70%;">https://pad.systemli.org/p/bhnt0${bhnt_no}</div>
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

EOF
echo '#############################################################################'

echo
echo 'Done.'
echo
