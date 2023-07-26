---
layout: slides
title: Berlin Hack & Tell \#89 - camping hacks
date: 2023-07-25
time: '19:00'
description: Slides for BHNT \#89
---


<section>
<center><b> BHNT #89 - camping hacks</b><br/>

<img src="/assets/images/088/camp.jpg"/><br/>


We start 1923 *sharpIsh*
 </center>	
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
<pre>https://pad.systemli.org/p/bhnt089</pre>
<iframe name="embed_readwrite" src="https://pad.systemli.org/p/bhnt089?showControls=false&showChat=false&showLineNumbers=true&useMonospaceFont=true" width="100%" height="600" frameborder="0" class="stretch"></iframe>
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
<img src="/assets/images/089/reddit.jpeg"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/089/stackoverflow_out.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/twitter_out.png"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/089/openai.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/ai_alignment.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/xai.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/gnosispay.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/monopoly.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/ethprague.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/orb.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/ledger.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/vanmoof.png"/>
</center>
</section>


<section>
<center>
<img src="/assets/images/089/twitterx.jpeg"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/mitnick.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/protocolberg.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/089/hardware_happy.png"/>
</center>
</section>

<section>
<center>
<img src="/assets/images/088/camp.jpg"/>
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
<div style="font-family: mono; font-size: 70%;">https://pad.systemli.org/p/bhnt089</div>
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
