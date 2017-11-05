#!/usr/bin/env node

'use strict';

const Rx = require('rxjs/Rx');

const fs = require('fs');
const slugger = require('slug');

const DATAFILE='bhnt.txt'
const nodeFileParser = require("node-file-parser")
const file = nodeFileParser.link(DATAFILE)

if(file === null) {
  Error("File not found.")
  return;
}

/*
# parse file for content
# split content into entries
# parse each entry into data class
# validate file content.
# valid: create a file per data class
# invalid: concact into error file
*/

readFile(file)
  .map(content => events(content))
  .flatMap(entry => Rx.Observable.from(entry)) // emit each SINGLE entry as Observable
  .filter(entry => entry.length) // ignore empty 'entries'
  //.skip(6)
  //.take(5)
  .flatMap(parseItem)
  .flatMap(prepareData)
  .subscribe(
    (data) => saveFile(data),
    err => console.error(err),
    () => console.log('done!')
  );


function readFile(data) {
  return Rx.Observable.of(data.read().getContent())
}

function events(content) {
    console.log("Read", content.length, "characters from file");
    let entries = content.split('\#\# ');
    console.log("Found",entries.length,"events in file");
    return entries
}

function parseItem(item) {

    let data = { hacks: []};

    let lines = item.split(/[\n]/)
    //console.log(lines);

    for (let fullLine of lines) {
      if(fullLine.startsWith('* ')) {
        data.hacks.push(fullLine)
      } else if(fullLine.match(/^[\d].*/)) {
        data.meta = fullLine;
      } else if(fullLine.match(/^[\w].*/)){
        data.title = fullLine
      }
    }

    //console.log(data);

    return Rx.Observable.of(data);
}

function prepareData(data){

  data.slug = slugger(data.title, {lower: true}).replace('berlin-hack-and-tell-','no');
  let pieces = data.meta.split(' | ');
  data.date = pieces[0];
  data.time = pieces[1];
  data.meetup = extractFromMarkdown(pieces[2])[2];
  data.photos = extractFromMarkdown(pieces[3])[2];
  data.location = pieces[4].replace('@','');

  data.filename = `${data.date}-${data.slug}.md`;

  if(data.hacks.length) {
    data.hacks = data.hacks.join('\n');
  } else {
    data.hacks = 'No hacks recorded yet. Do you know more? PRs are welcome!'
  }

  return Rx.Observable.of(data);
}

function extractFromMarkdown(markdown) {

  if(markdown) {
    let matches = markdown.match(/\[(.*)\]\((.*)\)/);
    if(matches != null && matches.length) return matches;
  }

  return ['','',''] //simplest solution
}

function saveFile(data) {
  logger(data);

  let content = generateContent(data);

  fs.writeFileSync(`../_posts/${data.filename}`, content)
}

function generateContent(data){
  return `---
layout: post
title: ${data.title}
date:   ${data.date} 13:37:42 +0100
time: '${data.time}'
location: '${data.location}'
meetupUrl: ${data.meetup}
photosUrl: ${data.photos}
---

${data.hacks}
`
}

function logger(data) {
  console.log(data);
  return Rx.Observable.of(data);
}
