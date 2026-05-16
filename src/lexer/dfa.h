#ifndef DFA_H
#define DFA_H

#include "stack.h"
#include <stdio.h>
#include "char_state.h"

enum STATE_SIGNAL {
	TRAVERSING,
	TOKEN_FOUND,
	EOF_FOUND,
	MALFORMED,
};

struct Automaton {
	FILE *filePointer;
	struct Stack* tokenStack;
	struct CharState* charState;
	enum STATE_SIGNAL (*nextState)(struct Automaton *self);
};

#endif
