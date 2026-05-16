#include "char_state.h"

int initState(struct CharState* charState) {
	charState->currentLexemeSize = 0;
	charState->currentLexeme[0] = '\0';
	charState->initState = initState;
	return 0;
}
