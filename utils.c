/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#include "utils.h"

// create a new transition
transition f(char ch, state_id next_state)
{
    transition t = (transition)malloc(sizeof(Transition));
    t->next_state = &states[next_state];
    t->next_char = ch;
    return t;
}

// create a transition for a to z except b to d
transition *aToZExceptBToD(state_id next_state)
{
    int size = 23;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (i != 'b' && i != 'c' && i != 'd')
        {
            transitions[j++] = f(i, next_state);
        }
    }
    return transitions;
}

// create a transition for a to z
transition *aToZ(state_id next_state)
{
    int size = 26;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for A to Z
transition *AToZ(state_id next_state)
{
    int size = 52;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    for (int i = 'A'; i <= 'Z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for b to d
transition *bToD(state_id next_state)
{
    int size = 3;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'b'; i <= 'd'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for 0 to 9
transition *zeroToNine(state_id next_state)
{
    int size = 10;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        transitions[j++] = f(i + '0', next_state);
    }
    return transitions;
}

// create a transition for 2 to 7
transition *twoToSeven(state_id next_state)
{
    int size = 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < 6; i++)
    {
        transitions[j++] = f(i + '2', next_state);
    }
    return transitions;
}

// Add remaining transitions to the graph
void theta(state_id curr_state, state_id next_state)
{
    int size = ALPHABET_SIZE - states[curr_state].length;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int count = 0;
    int *freq = (int *)calloc(128, sizeof(int));
    for (int j = 0; j < states[curr_state].length; j++)
    {
        freq[states[curr_state].transitions[j]->next_char] = 1;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (freq[ALPHABETS[i]] != 1)
        {
            transitions[count++] = f(ALPHABETS[i], next_state);
        }
    }
    add_transition(curr_state, transitions, size);
}

bool append_endline(char *file_name)
{
    // open the file in read mode, if the last character is not a newline character, open the file in append mode and append a newline character
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        cyan("File not found\n");
        return 0;
    }
    fseek(fp, -1, SEEK_END);
    char ch;
    fread(&ch, 1, 1, fp);
    if (ch != '\n')
    {
        fclose(fp);
        fp = fopen(file_name, "a");
        fprintf(fp, "\n");
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
    return 1;
}