#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data_structures/vector.h"
#include "data_structures/trie.h"

void theta(state_id curr_state, state_id next_state); // Add remaining transitions to the graph
transition f(char ch, state_id next_state);           // create a transition
transition *aToZExceptBToD(state_id next_state);      // create a transition for a to z except b to d
transition *aToZ(state_id next_state);                // create a transition for a to z
transition *AToZ(state_id next_state);                // create a transition for A to Z
transition *bToD(state_id next_state);                // create a transition for b to d
transition *zeroToNine(state_id next_state);          // create a transition for 0 to 9
transition *twoToSeven(state_id next_state);          // create a transition for 2 to 7

void append_endline(char *str);

// Adding colors to the output

#define yellow(x...)          \
    {                         \
        printf("\033[1;33m"); \
        printf(x);            \
        printf("\033[0m");    \
    }
#define red(x...)             \
    {                         \
        printf("\033[1;31m"); \
        printf(x);            \
        printf("\033[0m");    \
    }
#define green(x...)           \
    {                         \
        printf("\033[1;32m"); \
        printf(x);            \
        printf("\033[0m");    \
    }
#define blue(x...)            \
    {                         \
        printf("\033[1;34m"); \
        printf(x);            \
        printf("\033[0m");    \
    }
#define magenta(x...)         \
    {                         \
        printf("\033[1;35m"); \
        printf(x);            \
        printf("\033[0m");    \
    }

#define cyan(x...)            \
    {                         \
        printf("\033[1;36m"); \
        printf(x);            \
        printf("\033[0m");    \
    }

#define white(x...)           \
    {                         \
        printf("\033[1;37m"); \
        printf(x);            \
        printf("\033[0m");    \
    }
#endif