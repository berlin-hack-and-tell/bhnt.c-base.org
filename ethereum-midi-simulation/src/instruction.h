#ifndef LASH_NETSIMMIDI_INSTRUCTION_H_
#define LASH_NETSIMMIDI_INSTRUCTION_H_

enum lash_netsimmidi_instruction_type_e {
	LASH_NETSIMMIDI_IDLE,
	LASH_NETSIMMIDI_NODE,
	LASH_NETSIMMIDI_CONN,
	LASH_NETSIMMIDI_DIAL
};

enum lash_netsimmidi_instruction_state_e {
	LASH_NETSIMMIDI_NEW,
	LASH_NETSIMMIDI_PENDING,
	LASH_NETSIMMIDI_COMPLETED,
	LASH_NETSIMMIDI_CANCELLED
};

typedef struct {
	int state;
	char one;
	char other;
	char result[3];
} lash_netsimmidi_instruction_t;

void lash_netsimmidiInstructionReset(lash_netsimmidi_instruction_t *ins);
int lash_netsimmidiInstructionTranslate(lash_netsimmidi_instruction_t *ins, lash_netsimmidi_input_status_t *st);

#endif // LASH_NETSIMMIDI_INSTRUCTION_H_
