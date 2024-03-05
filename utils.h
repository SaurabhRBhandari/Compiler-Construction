/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"
#include "vector.h"
#include "trie.h"

// Adds a newline character at the end of the string and returns true if successful, false otherwise
bool append_endline(char *str);

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