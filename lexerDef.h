#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_BUFFER_SIZE 1000
#define MAX_STATES 150

const char alphabets[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                          'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                          'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                          'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                          'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2',
                          '3', '4', '5', '6', '7', '8', '9', ' ', '\n', '\t', '~',
                          '(', '[', ']', ')', '<', '>', '!', '@', '#', '%', '&',
                          '*', '_', '+', '-', '/', '=', ';', ':', '.', ','};

int line_count = 0;

typedef struct Transition
{
    char next_char;
    struct State *next_state;
} Transition;

typedef struct State
{
    int state_id;
    struct Transition **transitions;
    int length;
    bool is_final_state;
    int retract_count;
} State;

typedef struct TwinBuffer
{
    char primary_buffer[MAX_BUFFER_SIZE];
    char secondary_buffer[MAX_BUFFER_SIZE];
    int primary_buffer_index;
    int secondary_buffer_index;
} TwinBuffer;

typedef struct TokenInfo
{
    int *tokens;
    int token_count;
} TokenInfo;

typedef struct State *state;
typedef struct Transition *transition;
typedef struct TwinBuffer *twinBuffer;
typedef struct TokenInfo *tokenInfo;

State states[MAX_STATES];

typedef enum state_id
{
    START,
    TK_INVALID,
    TK_ASSIGNOP,
    TK_COMMENT,
    TK_FIELDID,
    TK_ID,
    TK_NUM_1,
    TK_NUM_2,
    TK_RNUM,
    TK_FUNID,
    TK_RUID,
    TK_WITH,
    TK_PARAMETERS,
    TK_END,
    TK_WHILE,
    TK_UNION,
    TK_ENDUNION,
    TK_DEFINETYPE,
    TK_AS,
    TK_TYPE,
    TK_MAIN,
    TK_GLOBAL,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_INPUT,
    TK_OUTPUT,
    TK_INT,
    TK_REAL,
    TK_COMMA,
    TK_SEM,
    TK_COLON,
    TK_DOT,
    TK_ENDWHILE,
    TK_OP,
    TK_CL,
    TK_IF,
    TK_THEN,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_RETURN,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_CALL,
    TK_RECORD,
    TK_ENDRECORD,
    TK_ELSE,
    TK_AND,
    TK_OR,
    TK_NOT,
    TK_LT_1,
    TK_LT_2,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    S_0,
    S_1,
    S_2,
    S_3,
    S_4,
    S_5,
    S_6,
    S_7,
    S_8,
    S_9,
    S_10,
    S_11,
    S_12,
    S_13,
    S_14,
    S_15,
    S_16,
    S_17,
    S_18,
    S_19,
    S_20,
    S_21,
    S_22,
    S_23,
    S_24,
    S_25,
    S_26,
    S_27,
    S_28,
    S_29,
    S_30,
    S_31,
    S_32,
    S_33,
    S_34,
    S_35,
    S_36,
    S_37,
    S_38,
    S_39,
    S_40,
    S_41,
    S_42,
    S_43,
    S_44,
    S_45,
    S_46,
    S_47,
    S_48,
    S_49,
    S_50,
    S_51,
    S_52,
    S_53,
    S_54,
    S_55,
    S_56,
    S_57,
    S_58,
    S_59,
    S_60,
    S_61
} state_id;

void add_state(state_id state_num, transition *transitions, int transition_count);

void initialize_states();

FILE *getStream(FILE *fp);

tokenInfo getNextToken(twinBuffer buffer);

state get_next_state(state current_state, char next_char);

transition *theta(char except_char, state_id next_state);

#define ALPHABET 27
typedef struct Trie
{
    struct Trie *characters[ALPHABET];
    state_id token;
} Trie;

typedef struct Trie *trie;

trie getTrieNode(void);
void insert(trie root, const char *key, state_id token);
state_id search(trie root, const char *key);
#undef ALPHABET
trie look_up_table;

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
// #define blue(x...)