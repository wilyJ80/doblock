#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/lexer/dfa.h"
#include "../src/lexer/states.h"
#include "../src/lexer/char_state.h"
#include <stdbool.h>
#define MAX_LEXEME_SIZE 512

int main()
{
	printf("[INFO] CREATING MOCK DATA\n");
	const char* mockData = "55 55 55";
	FILE *mockFile = fmemopen((void*)mockData, strlen(mockData), "r");
	if (mockFile == NULL) {
		fprintf(stderr, "[ERROR] Error opening source file.\n");
		exit(EXIT_FAILURE);
	}

	// TODO: make Lexer object encapsulate creation of structures
	printf("[INFO] CREATING STACK\n");
	struct Stack stack = {.initStack = initStack};
	stack.initStack(&stack);

	printf("[INFO] CREATING CHARSTATE\n");
	// TODO: Make charState object with init function
	struct CharState charState = {.initState = initState};
	charState.initState(&charState);

	printf("[INFO] CREATING AUTOMATON\n");
	struct Automaton automaton = {
		.filePointer = mockFile,
		.tokenStack = &stack,
		.charState = &charState,
		.nextState = start
	};

	printf("[INFO] STARTING DFA LOOP\n");
	while (true) {
		enum STATE_SIGNAL signal = automaton.nextState(&automaton);
		printf("SIGNAL %d\n", signal);
		printf("STATE %s\n", automaton.charState->currentLexeme);

		if (signal == MALFORMED) {
			fprintf(stderr, "[ERROR] Malformed token\n");
			// TODO: Report line error
			// optional: error type
			// error log: show malformed, show previous token, show line
			printf("%s Lexeme | \n", automaton.charState->currentLexeme);
			exit(EXIT_FAILURE);
		}

		if (signal == EOF_FOUND) {
			break;
		}

		// TODO: no need for token found signal?
	}

	assert(automaton.tokenStack->tokens[0] == INTCON);

	return EXIT_SUCCESS;
}
