#ifndef STATES_H
#define STATES_H

#include "dfa.h"

enum STATE_SIGNAL start(struct Automaton* automaton);

enum STATE_SIGNAL intcon(struct Automaton* automaton);

enum STATE_SIGNAL realcon(struct Automaton* automaton);

#endif
