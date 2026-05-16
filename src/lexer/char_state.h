#ifndef CHAR_STATE_H
#define CHAR_STATE_H

#define MAX_LEXEME_SIZE 512

struct CharState {
	char currentChar;
	char currentLexeme[MAX_LEXEME_SIZE];
	int currentLexemeSize;
	// method to update lexeme here
	// TODO: init char state
	int (*initState)(struct CharState* self);
};

int initState(struct CharState* charState);

#endif
