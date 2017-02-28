#include "midi.h"
#include "instruction.h"

void lash_netsimmidiInstructionReset(lash_netsimmidi_instruction_t *ins) {
	ins->state = LASH_NETSIMMIDI_NEW;
	ins->one = -1;
	ins->other = -1;
	memset(ins->result, 0, 3);
}

int lash_netsimmidiInstructionTranslate(lash_netsimmidi_instruction_t *ins, lash_netsimmidi_input_status_t *st) {
	switch (st->instruction) {
		case LASH_NETSIMMIDI_NOTEON:
			if (ins->state == LASH_NETSIMMIDI_PENDING && ins->result[0] == LASH_NETSIMMIDI_NODE) { // connect one node with another
				if (ins->one > -1 && ins->one != st->key) {
					ins->other = st->key;
					ins->result[2] = ins->other;
					ins->state = LASH_NETSIMMIDI_COMPLETED;
				}
			} else if (ins->state == LASH_NETSIMMIDI_NEW) {
				ins->state = LASH_NETSIMMIDI_PENDING;
				ins->one = st->key;
				ins->result[0] = LASH_NETSIMMIDI_NODE;
				ins->result[1] = st->key;
			} else {
				return -1;
			}
			break;
		case LASH_NETSIMMIDI_NOTEOFF:
			if (ins->state != LASH_NETSIMMIDI_PENDING)
				return -1;
			ins->state = LASH_NETSIMMIDI_COMPLETED;
			ins->result[0] = LASH_NETSIMMIDI_NODE;
			ins->result[1] = st->key;
			break;
		case LASH_NETSIMMIDI_CTRLCHANGE:
			ins->state = LASH_NETSIMMIDI_COMPLETED;
			ins->result[0] = LASH_NETSIMMIDI_DIAL;
			ins->result[1] = st->key;
			ins->result[2] = st->value;
			break;
		default:
			return -1;
	}
	return 0;
}
