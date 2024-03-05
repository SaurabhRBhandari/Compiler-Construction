/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar 
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#include "trie.h"
#define ALPHABET 27

// Returns a new trie node
trie getTrieNode(void)
{
    trie newNode = (trie)malloc(sizeof(Trie));
    newNode->token = TK_INVALID;
    for (int i = 0; i < ALPHABET; i++)
        newNode->characters[i] = NULL;
    return newNode;
}

// Inserts a key-value pair into the trie
void insert(trie root, const char *key, token_id token)
{
    int i, size = strlen(key), index;
    trie curr = root;
    for (i = 0; i < size; i++)
    {
        if (key[i] == '_')
            index = 26;
        else
            index = (int)key[i] - (int)'a';
        if (!curr->characters[index])
            curr->characters[index] = getTrieNode();
        curr = curr->characters[index];
    }
    curr->token = token;
}


// Searches for a key in the trie
token_id search(trie root, const char *key)
{
    int i, size = strlen(key), index;
    trie curr = root;
    for (i = 0; i < size; i++)
    {
        if (key[i] == '_')
            index = 26;
        else
            index = (int)key[i] - (int)'a';
        if (!curr->characters[index])
            return TK_INVALID;
        curr = curr->characters[index];
    }
    return curr->token;
}
#undef ALPHABET
