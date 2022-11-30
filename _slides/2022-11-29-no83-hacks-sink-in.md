---
layout: slides
title: Berlin Hack & Tell \#83 - Hacks sink in
date: 2022-09-27
time: '19:00'
description: Slides for BHNT #83
---

<section data-markdown>
## BHNT \#83 - Hacks sink in

![](/assets/images/083/intro.jpg)

We start 19:23 *sharpIsh*
</section>

<section data-markdown>
## Structure

1. Intro (this)
1. Rules
1. News
1. Slots 0..3
1. Flea market (everything goes)
1. Break
1. Slots 4..7
1. Vote at the end and Wanderpokal
1. (TBA) Black light table tennis
</section>

<section data-markdown>
## Rules

1. Be excellent to each other
2. Do not smoke
3. You get 5 minutes to present in English
4. You or your team should have built it yourself
5. People get 5 minutes Q&A afterwards
6. NO PURE SLIDEDECKS, no pitches, only demos + code
7. Show us code!!! (reasonable exemptions may be possible)
8. Entertain us!
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
<pre>https://pad.systemli.org/p/bhnt083</pre>
<iframe name="embed_readwrite" src="https://pad.systemli.org/p/bhnt83?showControls=false&showChat=false&showLineNumbers=true&useMonospaceFont=true" width="100%" height="600" frameborder="0" class="stretch"></iframe>
</section>

<section data-markdown>
![Hack and Tell Trophy]({{ '/assets/images/trophy.jpg' | relative_url }})
</section>

<section data-markdown>
## News
</section>

<section>
<center>
<img src="/assets/images/083/musk.webp"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/bird_free.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/nestle.jpeg"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/083/twitter_takeout.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/bhnt_mastodon.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/dverification.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/devcon.jpeg"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/083/sdp_devcon.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/snowden.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/reddit_onion.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/fdroid.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/kotlin.png"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/083/ibug.jpeg"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/083/keycard_plausible.png"/>
</center>
</section>






<section>
<center>
<img src="/assets/images/083/dex.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/crying_ape.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/nick_quiz.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/nick_quiz2.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/bhnt_sd.jpg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/bhnt_sd2.jpg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/artemis.jpeg"/>
</center>
</section>

<section>
<center>
<h1>Upcoming Events</h1>
</center>
</section>


<section>
<center>
<img src="/assets/images/083/android.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/083/ethindia.png"/>
</center>
</section>



<section>
<center>
<img src="/assets/images/083/hip.svg"/>
</center>
</section>

<section data-markdown>
## News from the audience

Open Source, the next version of XY, events...
</section>

<section data-markdown>
This slide is intentionally left blankIsh
</section>

<section data-markdown>
## Flea market

1. Line up at the stage
2. Stick to 1-2 sentences
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
    var total = 170;
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
<img src="http://api.qrserver.com/v1/create-qr-code/?color=000000&amp;bgcolor=FFFFFF&amp;data=http%3A%2F%2Fpad.systemli.org%2Fp%2Fbhnt082&amp;qzone=1&amp;margin=0&amp;size=300x300&amp;ecc=L" alt="QR code">
<div style="font-family: mono; font-size: 70%;">https://pad.systemli.org/p/bhnt082</div>
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
