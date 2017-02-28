# ethereum p2p - midi ctrl

Example of interfacing with lowlevel ALSA and internet sockets to feed the current [D3 network visualizer](https://github.com/nolash/simple-p2p-d3/tree/hackntell) hack for the [Ethereum P2P network simulation](https://github.com/nolash/ethereum/go-ethereum/tree/hackntell).

- Maintains a buffer of MIDI data "translated" to network sim ctrl input.
- Maintains a tcp listener to feed this data upon request.

Tested with an AKAI MPD24. 

## Procedure

- Make this (handmade Makefile for home cooking. Make your own if you need)-
- Find your MIDI alsa hw
- Run `bin/midinetworksim`
- Run `client/index.html` in browser and verify midi feed to browser.
- Run go-ethereum `p2p/simulations/examples/connectivity.go` (see link above)
- Run `simple-p2p-d3  (see link above) NB! CORS caveats, the PUTs are dicey

First Note on - off combo creates and node, second brings it up.

Note on on two notes before off creates connection between nodes in question (provided they're up).

The javascript client has hardcoded note 1-16 capacity.

## Contact

BM-NBXpv4oRf2BkNLJBZAm2muikBsm6EzvW
