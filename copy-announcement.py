import atproto
import datetime
import re
import zoneinfo

def generate_post_file(filepath, start, no, title, openmeet_rsvp_uri):
    print(f'Generating post file {filepath} ...')
    with open(filepath, 'w') as f:
        f.write(
fr'''---
layout: post
title: Berlin Hack & Tell \#{no} - {title}
published: true
date: {start:%Y-%m-%d}
time: '{start:%H:%M}'
location: '[c-base](https://www.c-base.org)'
---

Please [RSVP here]({openmeet_rsvp_uri})
''')

def generate_slides_file(filepath, start, no, title):
    print(f'Generating slides file {filepath} ...')
    with open(filepath, 'w') as f:
        f.write(
fr'''---
layout: slides
title: Berlin Hack & Tell \#{no} - {title}
date: {start:%Y-%m-%d}
time: '{start:%H:%M}'
description: Slides for BHNT \#{no}
---

<section data-background-size="contain" data-background="/assets/images/{no}/logo.png"></section>
<section data-background-size="contain" data-background="/assets/images/bhntflow.svg"></section>

<section>
<h2>Constraints §</h2>
</section>

<section data-markdown>
## 🚀
Be future compatible
</section>

<section data-markdown>
## 👽
All creatures welcome
</section>

<section data-markdown>
## 🙋
Participate
</section>  

<section data-markdown>
## &#128247;
<center>
No photo without consent
</center>
</section>

<section data-markdown>
## 📳🤫🎤
<center>
max(Signal/Noise)
</center>
</section>

<section data-markdown>
## 🥦🚬🚪
<center>
Only smoke outside
</center>
</section>

<section data-markdown>
## 5️⃣ ⌛❣️
<center>
Respect the 5min
</center>
</section>

<section data-markdown>
## 🫵
<center>
Show *Your* thing
</center>
</section>

<section data-markdown>
## 🚫💸👔
<center>
No business
</center>
</section>

<section data-markdown>
## 🎓🤯🍿
<center>
Edutain us
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

<section data-background-size="contain" data-background="/assets/images/trophy.jpg"></section>

<section data-background-size="contain" data-background="/assets/images/trophies.jpg"></section>

<section data-markdown>
## Global Infrastructure
* www: https://bhnt.c-base.org
* md: https://md.c-base.org/bhnt-{no}
* ATmosphere at://bhnt.c-base.org
 * BlueSky
 * SmokeSignal / OpenMeet
* matrix: #bhnt:c-base.org #BHNTNews:matrix.org
* HashTag: #BHNT{no}
* Mastodon: https://chaos.social/@BHNT
* X: https://twitter.com/BerlinHacknTell
</section>

<section data-background-size="contain" data-background="/assets/images/bhntflow_warmup.svg"></section>

<section data-markdown>
## Events
</section>

<section data-background-size="contain" data-background="/assets/images/{no}/last.jpg"></section>

<section data-markdown>
## AI AI AI
</section>

<section data-background-size="contain" data-background="/assets/images/{no}/..."></section>

<section data-markdown>
## HardWare
</section>

<section data-background-size="contain" data-background="/assets/images/{no}/..."></section>

<section data-markdown>
## PoliTriX
</section>

<section data-background-size="contain" data-background="/assets/images/{no}/..."></section>

<section data-markdown>
## CRYpto
</section>

<section data-background-size="contain" data-background="/assets/images/{no}/..."></section>

<section data-background-size="contain" data-background="/assets/images/bhntflow_hacks.svg"></section>

<section data-markdown>
## Open(ishaa) Mic 🎤

Stick to 1-2 sentences

</section>

<section>
<h2>Break</h2>

<ul>
<li>Until <input style="margin-left: 0.2em; font-size: 100%; width: 4em; border: 1px solid white; background-color: transparent; color: white; text-align: center;"></li>
<li>Bottles back to the bar</li>
<li>Update your presentation details:</li>
</ul>
<center>
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=https%3A%2F%2Fmd.c-base.org%2Fbhnt-{no}&amp;qzone=1&amp;margin=0&amp;size=300x300&amp;ecc=L" alt="QR code">
<div style="font-family: mono; font-size: 70%;">https://md.c-base.org/bhnt-{no}</div>
</center>
</section>

<section>
<h2>Vote</h2>

<ul>
<li>wifi:c-base-public</li>
<li>pw:hacktheplanet</li>
<li>http://172.31.78.206</li>
</ul>
<center>
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=http%3A%2F%2F172.31.78.206&amp;qzone=1&amp;margin=0&amp;size=400x400&amp;ecc=L" alt="QR code">
</center>
</section>

<section data-background-size="contain" data-background="/assets/images/bhntflow_handover.svg"></section>
''')

def main():
    base_url = 'https://bsky.social'
    bhnt_did = 'did:plc:mho5wxz2wvccynomj7r2zxaz'
    print('Fetching list of events ...')
    client_pub = atproto.Client(base_url)
    result = client_pub.com.atproto.repo.list_records(
        atproto.models.com.atproto.repo.list_records.Params(
            repo=bhnt_did,
            collection='community.lexicon.calendar.event',
        )
    )
    print('Extracting details of upcoming event ...')
    event = result.records[0].value
    start_utc = datetime.datetime.fromisoformat(event.startsAt)
    start = start_utc.astimezone(zoneinfo.ZoneInfo('Europe/Berlin'))
    name = event.name
    try:
        no, title = re.fullmatch(r'^BHNT #([0-9]+) - (\S.*\S)$', name).groups()
    except AttributeError:
        raise RuntimeError(f'Unable to parse event name: {name!r}')
    uris = event.uris
    try:
        [openmeet_rsvp_uri] = [
            u.uri
            for u in event.uris
            if u.source == 'net.openmeet'
            and u.name == 'OpenMeet Event'
        ]
    except ValueError:
        raise RuntimeError(f'Unable to determine OpenMeet RSVP URI from URI list: {uris!r}')
    title_in_filename = re.sub('[^0-9a-z]+', '-', title.lower()).strip('-')
    filename = f'{start:%Y-%m-%d}-no{no}-{title_in_filename}.md'
    generate_post_file(f'_posts/{filename}', start=start, no=no, title=title, openmeet_rsvp_uri=openmeet_rsvp_uri)
    generate_slides_file(f'_slides/{filename}', start=start, no=no, title=title)
    print('Finished.')

main()
