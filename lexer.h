/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar 
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef LEXER_H
#define LEXER_H
#include "utils.h"

void add_state(state_id state_num, transition *transitions, int transition_count); // Add a state to the graph

void initialize_states(); // Initialize the states of the graph

void initialize_transitions(); // Initialize the transitions of the graph

void initialize_lookup_table(); // Initialize the lookup table

state get_next_state(state current_state, char next_char); // Get the next state from the current state and the next character

void add_transition(state_id state, transition *transitions, int transition_count); // Add a transition to the graph

tokenInfo getNextToken(twinBuffer buffer); // Get the next token from the buffer

void removeComments(char *testcaseFile, char *cleanFile);

#ifndef VECTOR_INCOMPLETE
#include "vector.h"
vector getStream(FILE *fp);
#endif
#endif