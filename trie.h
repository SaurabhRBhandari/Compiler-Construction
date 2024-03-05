/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef TRIE_H
#define TRIE_H
#define ALPHABET 27
#define TRIE_INCOMPLETE
#include "lexerDef.h"

// Trie node
typedef struct Trie
{
    struct Trie *characters[ALPHABET];
    token_id token;
} Trie;
typedef struct Trie *trie;

// Returns a new trie node
trie getTrieNode(void);

// Inserts a key-value pair into the trie
void insert(trie root, const char *key, token_id token);

// Searches for a key in the trie
token_id search(trie root, const char *key);

#undef ALPHABET
#undef TRIE_INCOMPLETE
#endif