#ifndef LASH_NETSIMMIDI_H_
#define LASH_NETSIMMIDI_H_

#include <alsa/asoundlib.h>

enum lash_netsimmidi_ctrl_e {
	LASH_NETSIMMIDI_NOTEOFF = 0x08,
	LASH_NETSIMMIDI_NOTEON = 0x09,
	LASH_NETSIMMIDI_CTRLCHANGE = 0x0b
};

typedef struct {
	unsigned char channel;
	unsigned char key;
	unsigned char instruction;
	unsigned char value;
	unsigned char sub_instruction;
	unsigned char sub_value;
} lash_netsimmidi_input_status_t;

typedef struct {
	int initialized;
	lash_netsimmidi_input_status_t is;
	snd_rawmidi_t *in;
	snd_rawmidi_status_t *s;
	unsigned char *ch;
	unsigned char raw[3];
} lash_netsimmidi_input_midi_t;


int lash_netsimmidiInit(lash_netsimmidi_input_midi_t *m, const char *ascid);
int lash_netsimmidiGet(lash_netsimmidi_input_midi_t *m);
void lash_netsimmidiClear(lash_netsimmidi_input_midi_t *m);
void lash_netsimmidiStatusClear(lash_netsimmidi_input_status_t *is);

#endif // LASH_NETSIMMIDI_H_
