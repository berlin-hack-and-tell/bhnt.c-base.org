#ifndef LASH_NETSIMMIDI_DEBUG_H_
#define LASH_NETSIMMIDI_DEBUG_H_

const char *lash_netsimmidi_debug_instruction_description[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"NoteOff",
	"NoteOn",
	"",
	"ControlChange",
	"",
	"Aftereffect",
	"",
	"SysEx"
};

typedef struct {
	unsigned char data[3];
} lash_netsimmidi_debug_input_t;



#endif // LASH_NETSIMMIDI_DEBUG_H_
