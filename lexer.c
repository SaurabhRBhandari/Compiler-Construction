#ifndef LEXERDEF_H
#include "lexerDef.h"
#define LEXERDEF_H
#endif

// TODO: move trie to other file
// TODO: Deal with function_id and variable_id (S_45)
#define ALPHABET 27
trie getTrieNode(void)
{
    trie newNode = (trie)malloc(sizeof(Trie));
    newNode->token = TK_INVALID;
    for (int i = 0; i < ALPHABET; i++)
        newNode->characters[i] = NULL;
    return newNode;
}

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

token getNewToken(token_id id, int lc, char *lexeme)
{
    token newToken = (token)malloc(sizeof(Token));
    newToken->tk = id;
    newToken->lc = lc;
    newToken->lexeme = (char *)(malloc(30 * sizeof(char)));
    strncpy(newToken->lexeme, lexeme, strlen(lexeme));
    return newToken;
}

void add_transition(state_id state, transition *transitions, int transition_count)
{
    int new_length = states[state].length + transition_count;
    states[state].transitions = (transition *)realloc(states[state].transitions, new_length * sizeof(transition));
    for (int i = 0; i < transition_count; i++)
    {
        states[state].transitions[states[state].length + i] = transitions[i];
    }
    states[state].length = new_length;
}

transition f(char ch, state_id next_state)
{
    transition t = (transition)malloc(sizeof(Transition));
    t->next_state = &states[next_state];
    t->next_char = ch;
    return t;
}

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

void theta(state_id curr_state, state_id next_state)
{
    // TODO: Write O(n) code instead
    int size = ALPHABET_SIZE - states[curr_state].length;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        bool flag = false;
        for (int j = 0; j < states[curr_state].length; j++)
        {
            if (states[curr_state].transitions[j]->next_char == ALPHABETS[i])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            transitions[j++] = f(ALPHABETS[i], next_state);
        }
    }
    add_transition(curr_state, transitions, size);
}
void initialize_states()
{
    for (int i = 0; i < MAX_STATES; i++)
    {
        states[i].length = 0;
        states[i].state_id = i;
        states[i].retract_count = 0;
        states[i].token = -1;
        states[i].transitions = NULL;
    }
    states[INVALID].token = TK_INVALID;
    states[S_1].token = TK_NOTOKEN;
    states[S_2].token = TK_NOTOKEN;
    states[S_3].token = TK_NOTOKEN;  // TODO: lc++
    states[S_43].token = TK_NOTOKEN; // TODO: lookup
    states[S_45].token = TK_NOTOKEN; // TODO: lookup
    states[S_60].token = TK_NOTOKEN;
    states[S_4].token = TK_NOT;
    states[S_5].token = TK_SQL;
    states[S_6].token = TK_SQR;
    states[S_7].token = TK_COMMA;
    states[S_8].token = TK_SEM;
    states[S_9].token = TK_COLON;
    states[S_10].token = TK_DOT;
    states[S_11].token = TK_OP;
    states[S_12].token = TK_CL;
    states[S_14].token = TK_EQ;
    states[S_15].token = TK_PLUS;
    states[S_16].token = TK_MINUS;
    states[S_18].token = TK_NE;
    states[S_21].token = TK_OR;
    states[S_24].token = TK_AND;
    states[S_27].token = TK_RUID;
    states[S_28].token = TK_MUL;
    states[S_30].token = TK_GT;
    states[S_31].token = TK_GE;
    states[S_33].token = TK_LT;
    states[S_34].token = TK_LE;
    states[S_36].token = TK_LT;
    states[S_38].token = TK_ASSIGNOP;
    states[S_39].token = TK_DIV;
    states[S_49].token = TK_ID;
    states[S_51].token = TK_NUM;
    states[S_55].token = TK_RNUM;
    states[S_58].token = TK_RNUM;
    states[S_61].token = TK_NUM;
    states[S_27].retract_count = 1;
    states[S_30].retract_count = 1;
    states[S_33].retract_count = 1;
    states[S_36].retract_count = 2;
    states[S_43].retract_count = 1;
    states[S_45].retract_count = 1;
    states[S_49].retract_count = 1;
    states[S_51].retract_count = 1;
    states[S_55].retract_count = 1;
    states[S_61].retract_count = 2;
    states[INVALID].retract_count = 1;
}

void initialize_transitions()
{
    add_transition(START, (transition[]){f('%', S_0), f(' ', S_2), f('\n', S_3), f('~', S_4), f('[', S_5), f(']', S_6), f(',', S_7), f(';', S_8), f(':', S_9), f('.', S_10), f('(', S_11), f(')', S_12), f('=', S_13), f('+', S_15), f('-', S_16), f('!', S_17), f('@', S_19), f('&', S_22), f('#', S_25), f('*', S_28), f('>', S_29), f('<', S_32), f('/', S_39), f('_', S_40), f('\t', S_60)}, 25);
    add_transition(START, bToD(S_46), 3);
    add_transition(START, zeroToNine(S_50), 10);
    add_transition(START, aToZExceptBToD(S_44), 23);
    add_transition(S_0, (transition[]){f('\n', S_1)}, 1);
    theta(S_0, S_0);
    add_transition(S_13, (transition[]){f('=', S_14)}, 1);
    add_transition(S_17, (transition[]){f('=', S_18)}, 1);
    add_transition(S_19, (transition[]){f('@', S_20)}, 1);
    add_transition(S_20, (transition[]){f('@', S_21)}, 1);
    add_transition(S_22, (transition[]){f('&', S_23)}, 1);
    add_transition(S_23, (transition[]){f('&', S_24)}, 1);
    add_transition(S_25, aToZ(S_26), 26);
    add_transition(S_26, aToZ(S_26), 26);
    theta(S_26, S_27);
    add_transition(S_29, (transition[]){f('=', S_31)}, 1);
    theta(S_29, S_30);
    add_transition(S_32, (transition[]){f('=', S_34), f('-', S_35)}, 2);
    theta(S_32, S_33);
    add_transition(S_35, (transition[]){f('-', S_37)}, 1);
    theta(S_35, S_36);
    add_transition(S_37, (transition[]){f('-', S_38)}, 1);
    add_transition(S_40, AToZ(S_41), 52);
    add_transition(S_41, AToZ(S_41), 52);
    add_transition(S_41, zeroToNine(S_42), 10);
    theta(S_41, S_43);
    add_transition(S_42, zeroToNine(S_42), 10);
    theta(S_42, S_43);
    add_transition(S_44, aToZ(S_44), 26);
    theta(S_44, S_45);
    add_transition(S_46, aToZ(S_44), 26);
    add_transition(S_46, twoToSeven(S_47), 6);
    add_transition(S_47, bToD(S_47), 3);
    add_transition(S_47, twoToSeven(S_48), 6);
    theta(S_47, S_49);
    add_transition(S_48, twoToSeven(S_48), 6);
    theta(S_48, S_49);
    add_transition(S_50, (transition[]){f('.', S_52)}, 1);
    add_transition(S_50, zeroToNine(S_50), 10);
    theta(S_50, S_51);
    add_transition(S_52, zeroToNine(S_53), 10);
    theta(S_52, S_61);
    add_transition(S_53, zeroToNine(S_54), 10);
    add_transition(S_54, (transition[]){f('E', S_56)}, 1);
    theta(S_54, S_55);
    add_transition(S_56, (transition[]){f('+', S_59), f('-', S_59)}, 2);
    add_transition(S_56, zeroToNine(S_57), 10);
    add_transition(S_57, zeroToNine(S_58), 10);
    add_transition(S_59, zeroToNine(S_57), 10);
}

void initialize_lookup_table()
{
    look_up_table = getTrieNode();
    insert(look_up_table, "with", TK_WITH);
    insert(look_up_table, "parameters", TK_PARAMETERS);
    insert(look_up_table, "end", TK_END);
    insert(look_up_table, "while", TK_WHILE);
    insert(look_up_table, "union", TK_UNION);
    insert(look_up_table, "endunion", TK_ENDUNION);
    insert(look_up_table, "definetype", TK_DEFINETYPE);
    insert(look_up_table, "as", TK_AS);
    insert(look_up_table, "type", TK_TYPE);
    insert(look_up_table, "_main", TK_MAIN);
    insert(look_up_table, "global", TK_GLOBAL);
    insert(look_up_table, "parameter", TK_PARAMETER);
    insert(look_up_table, "list", TK_LIST);
    insert(look_up_table, "input", TK_INPUT);
    insert(look_up_table, "output", TK_OUTPUT);
    insert(look_up_table, "int", TK_INT);
    insert(look_up_table, "real", TK_REAL);
    insert(look_up_table, "endwhile", TK_ENDWHILE);
    insert(look_up_table, "if", TK_IF);
    insert(look_up_table, "then", TK_THEN);
    insert(look_up_table, "endif", TK_ENDIF);
    insert(look_up_table, "read", TK_READ);
    insert(look_up_table, "write", TK_WRITE);
    insert(look_up_table, "return", TK_RETURN);
    insert(look_up_table, "call", TK_CALL);
    insert(look_up_table, "record", TK_RECORD);
    insert(look_up_table, "endrecord", TK_ENDRECORD);
    insert(look_up_table, "else", TK_ELSE);
}

// print the graph, for debugging
void print_graph()
{
    FILE *fp = fopen("graph.txt", "w");
    for (int i = 0; i < MAX_STATES; i++)
    {
        // blue("%d : ", i);
        fprintf(fp, "%d : ", i);
        for (int j = 0; j < states[i].length; j++)
        {
            // blue("\t[%c -> %d] ", states[i].transitions[j]->next_char, states[i].transitions[j]->next_state->state_id);
            fprintf(fp, "\t[%c -> %d] ", states[i].transitions[j]->next_char, states[i].transitions[j]->next_state->state_id);
        }
        // blue("\n\n\n");
        fprintf(fp, "\n\n\n");
    }
}

FILE *getStream(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error: File not found\n");
        exit(1);
    }
    twinBuffer buffer = (twinBuffer)malloc(sizeof(struct TwinBuffer));
    buffer->secondary_buffer_index = 0;
    buffer->line_count = 1;
    FILE *new_fp = fopen("a.salad", "w");
    if (new_fp == NULL)
    {
        printf("Error: Could not create a new file\n");
        exit(1);
    }
    while (fgets(buffer->primary_buffer, MAX_BUFFER_SIZE, fp) != NULL)
    {
        tokenInfo info = getNextToken(buffer);
        for (int i = 0; i < info->token_count; i++)
        {
            fprintf(new_fp, "Line: %d,  Lexeme: %s, Token: %s\n", info->tokens[i]->lc, info->tokens[i]->lexeme, TOKENS[info->tokens[i]->tk]);
        }
    }
    fclose(fp);
    return new_fp;
}

tokenInfo getNextToken(twinBuffer buffer)
{
    state curr_state = &states[START];
    state prev_state = NULL;
    buffer->primary_buffer_index = 0;

    tokenInfo tokens = (tokenInfo)malloc(sizeof(TokenInfo));
    tokens->tokens = (token *)malloc(MAX_BUFFER_SIZE * sizeof(token));
    tokens->token_count = 0;

    char *keyword = (char *)malloc(100 * sizeof(char));

    int till = 0;

    int is_filled = buffer->secondary_buffer_index > 0;

    int token_len = 0;
    int token_count = 0;
    int next = 1;

    while (till < buffer->secondary_buffer_index)
    {

        curr_state = get_next_state(curr_state, buffer->secondary_buffer[till]);
        printf("%d %c he\n", curr_state->state_id, buffer->secondary_buffer[till]);
        token_len++;
        if (curr_state->token == TK_INVALID)
        {
            int next = (token_len == 1);
            buffer->primary_buffer_index -= curr_state->retract_count;
            token_len -= curr_state->retract_count;
            memset(keyword, '\0', 30);
            strncpy(keyword, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, token_len + next);
            tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
            tokens->token_count++;
            buffer->primary_buffer_index++;
            buffer->primary_buffer_index += next;
            token_len = 0;
            curr_state = &states[START];
            continue;
        }
        till -= curr_state->retract_count;
        token_len -= curr_state->retract_count;
        if (curr_state->token != -1)
        {
            memset(keyword, '\0', 30);
            strncpy(keyword, buffer->secondary_buffer + till - token_len + 1, token_len);
            if (curr_state->state_id == S_43 || curr_state->state_id == S_45)
            {
                token_id tk = search(look_up_table, keyword);
                tokens->tokens[tokens->token_count] = getNewToken(tk, buffer->line_count, keyword);
                tokens->token_count++;
                green("%s\n", keyword);
            }
            if (curr_state->token != TK_NOTOKEN)
            {
                tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
                tokens->token_count++;
            }
            curr_state = &states[START];
            token_len = 0;
        }
        till++;
        prev_state = curr_state;
    }

    if (is_filled)
    {
        memset(buffer->secondary_buffer, '\0', MAX_BUFFER_SIZE);
    }

    // read from primary buffer
    while (buffer->primary_buffer_index < MAX_BUFFER_SIZE && buffer->primary_buffer[buffer->primary_buffer_index] != '\0')
    {

        curr_state = get_next_state(curr_state, buffer->primary_buffer[buffer->primary_buffer_index]);
        green("%c %d\n", buffer->primary_buffer[buffer->primary_buffer_index], buffer->primary_buffer_index);
        token_len++;
        if (buffer->primary_buffer[buffer->primary_buffer_index] == '\n' && curr_state->retract_count == 0)
        {
            buffer->line_count++;
        }
        if (curr_state->token == TK_INVALID)
        {
            int next = (token_len == 1);
            buffer->primary_buffer_index -= curr_state->retract_count;
            token_len -= curr_state->retract_count;
            memset(keyword, '\0', 30);
            strncpy(keyword, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, token_len + next);
            tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
            tokens->token_count++;
            buffer->primary_buffer_index++;
            buffer->primary_buffer_index += next;
            token_len = 0;
            curr_state = &states[START];
            continue;
        }
        buffer->primary_buffer_index -= curr_state->retract_count;
        token_len -= curr_state->retract_count;
        if (curr_state->token != -1)
        {

            memset(keyword, '\0', 30);
            strncpy(keyword, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, token_len);
            green("%s %d %d\n", keyword, token_len, buffer->primary_buffer_index);
            if (curr_state->state_id == S_43 || curr_state->state_id == S_45)
            {
                token_id tk = search(look_up_table, keyword);
                tokens->tokens[tokens->token_count] = getNewToken(tk, buffer->line_count, keyword);
                tokens->token_count++;
                green("%s\n", keyword);
            }
            if (curr_state->token != TK_NOTOKEN)
            {
                tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
                tokens->token_count++;
            }
            curr_state = &states[START];
            token_len = 0;
        }
        buffer->primary_buffer_index++;
    }

    if (curr_state == &states[S_0])
    {
        strncpy(buffer->secondary_buffer, "%", 1);
        buffer->secondary_buffer_index = 1;
    }
    else if (curr_state != &states[START])
    {
        strncpy(buffer->secondary_buffer, buffer->primary_buffer + MAX_BUFFER_SIZE - 1 - token_len, token_len + (token_len == 0));
        buffer->secondary_buffer_index = token_len;
    }
    else
    {
        buffer->secondary_buffer_index = 0;
    }
    return tokens;
}

state get_next_state(state current_state, char next_char)
{
    bool flag = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (ALPHABETS[i] == next_char)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        return &states[INVALID];
    }
    for (int i = 0; i < current_state->length; i++)
    {
        if (current_state->transitions[i]->next_char == next_char)
        {
            blue("1. %d %c \n", current_state->token, next_char);
            return current_state->transitions[i]->next_state;
        }
    }
    blue("2. %d %c \n", current_state->token, next_char);
    return &states[INVALID];
}

int main()
{
    initialize_states();
    initialize_transitions();
    initialize_lookup_table();
    FILE *fp = fopen("test_cases/t1.txt", "r");
    FILE *new_fp = getStream(fp);
    fclose(new_fp);
    return 0;
}