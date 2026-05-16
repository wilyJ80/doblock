#include "states.h"
#include "dfa.h"
#include <stdio.h>
#include <ctype.h>

// TODO: Make this a method of a separate lexeme object
void _updateLexeme(struct Automaton* automaton, int chcode) {
	char* lexeme = automaton->charState->currentLexeme;
	int size = automaton->charState->currentLexemeSize;
	lexeme[size] = chcode;
	lexeme[size++] = '\0';
}

/*
 * DFA works by
 * updating the runtime state signal,
 * updating char state,
 * updating top token in stack,
 * and pointing to next state.
	*/
enum STATE_SIGNAL start(struct Automaton* automaton) {
	int chcode = fgetc(automaton->filePointer);
	// If EOF, stop immediately
	if (chcode == EOF) {
		return EOF_FOUND;
	}
	automaton->charState->currentChar = chcode;

	// nonprinting: ignore
	if (!isprint(chcode)) {
		return TRAVERSING;
	}

	// check following states
	if (isdigit(chcode)) {
		_updateLexeme(automaton, chcode);

		automaton->nextState = intcon;
		return TRAVERSING;
	}
	
	// report malformed if no transition found
	return MALFORMED;
}

enum STATE_SIGNAL intcon(struct Automaton* automaton) {
	int chcode = fgetc(automaton->filePointer);
	// return intcon if appropriate
	if (chcode == EOF) {
		_updateLexeme(automaton, chcode);

		struct Stack* stack = automaton->tokenStack;
		stack->addItem(stack, INTCON);
		automaton->nextState = start;
		return TOKEN_FOUND;
	}
	// loop intcon if appropriate
	if (isdigit(chcode)) {
		_updateLexeme(automaton, chcode);

		automaton->nextState = intcon;
		return TRAVERSING;
	}

	// point to realcon if appropriate
	if (chcode == '.') {
		_updateLexeme(automaton, chcode);

		automaton->nextState = realcon;
		return TRAVERSING;
	}

	return MALFORMED;
}

enum STATE_SIGNAL realcon(struct Automaton* automaton) {
	int chcode = fgetc(automaton->filePointer);
	// return realcon if appropriate
	if (chcode == EOF) {
		_updateLexeme(automaton, chcode);
		struct Stack* stack = automaton->tokenStack;
		stack->addItem(stack, REALCON);
		automaton->nextState = start;
		return TOKEN_FOUND;
	}

	// keep building otherwise
	if (isdigit(chcode)) {
		_updateLexeme(automaton, chcode);
		automaton->nextState = realcon;
		return TRAVERSING;
	}

	return MALFORMED;
}
