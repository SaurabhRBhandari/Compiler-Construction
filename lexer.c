#ifndef LEXERDEF_H
#include "lexerDef.h"
#define LEXERDEF_H
#endif

#define ALPHABET 27
trie getTrieNode(void)
{
    trie newNode = (trie)malloc(sizeof(Trie));
    newNode->token = TK_INVALID;
    for (int i = 0; i < ALPHABET; i++)
        newNode->characters[i] = NULL;
    return newNode;
}

void insert(trie root, const char *key, state_id token)
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

state_id search(trie root, const char *key)
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
            return TK_INVALID; // Rotten Vegetable
        curr = curr->characters[index];
    }
    return curr->token; // type of vegetable
}
#undef ALPHABET

void add_state(state_id state, transition *transitions, int transition_count)
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

transition *theta(char except_char, state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 1;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if (alphabets[i] != except_char)
        {
            transitions[j++] = f(alphabets[i], next_state);
        }
    }
    return transitions;
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

transition *theta32(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 3 - 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if (alphabets[i] == '-' || alphabets[i] == '=')
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta41(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 2;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {

        if ((alphabets[i] >= 'a' && alphabets[i] <= 'z') || (alphabets[i] >= 'A' && alphabets[i] <= 'Z') || (alphabets[i] >= '0' && alphabets[i] <= '9'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta42(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 10;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {

        if ((alphabets[i] >= '0' && alphabets[i] <= '9'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta44(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 26;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {

        if ((alphabets[i] >= 'a' && alphabets[i] <= 'z'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta47(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 3 - 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if ((alphabets[i] >= 'b' && alphabets[i] <= 'd') || (alphabets[i] >= '2' && alphabets[i] <= '7'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta48(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if (alphabets[i] >= '2' && alphabets[i] <= '7')
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta50(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 11;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if (alphabets[i] == '.' || (alphabets[i] >= '0' && alphabets[i] <= '9'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta52(state_id next_state)
{
    int size = sizeof(alphabets) / sizeof(char) - 10;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < sizeof(alphabets) / sizeof(char); i++)
    {
        if ((alphabets[i] >= '0' && alphabets[i] <= '9'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

void initialize_states()
{
    for (int i = 0; i < MAX_STATES; i++)
    {
        states[i].length = 0;
        states[i].state_id = i;
        if (i > START && i <= TK_NE)
        {
            states[i].is_final_state = true;
        }
        else
        {
            states[i].is_final_state = false;
        }
        if (i == S_45 || i == S_43 || i == S_60 || i == S_3 || i == S_2 || i == S_1)
        {
            states[i].is_final_state = true;
        }
        states[i].retract_count = 0;
    }
    states[TK_RUID].retract_count = 1;
    states[S_43].retract_count = 1;
    states[S_45].retract_count = 1;
    states[TK_RNUM].retract_count = 1;
    states[TK_NUM_1].retract_count = 1;
    states[TK_NUM_2].retract_count = 1;
    states[TK_LT_1].retract_count = 2;
    states[TK_LT_2].retract_count = 2;
    states[TK_GT].retract_count = 1;
    states[TK_ID].retract_count = 1;

    int theta_size = sizeof(alphabets) / sizeof(char) - 1;
    int total_size = theta_size + 1;

    add_state(START, (transition[]){f('%', S_0), f(' ', S_2), f('@', S_19), f('&', S_22), f('#', S_25), f('*', TK_MUL), f('>', S_29), f('<', S_32), f('/', TK_DIV), f('\t', S_60), f('\n', S_3), f('~', TK_NOT), f('[', TK_SQL), f(']', TK_SQR), f(',', TK_COMMA), f(';', TK_SEM), f(':', TK_COLON), f('.', TK_DOT), f('(', TK_OP), f(')', TK_CL), f('=', TK_EQ), f('+', TK_PLUS), f('-', TK_MINUS), f('!', S_17), f('_', S_40)}, 25);
    add_state(START, bToD(S_46), 3);
    add_state(START, zeroToNine(S_50), 10);
    add_state(START, aToZExceptBToD(S_44), 23);
    add_state(S_0, (transition[]){f('\n', S_1)}, 1);
    add_state(S_0, theta('\n', S_0), theta_size);
    add_state(S_13, (transition[]){f('=', TK_EQ)}, 1);
    add_state(S_17, (transition[]){f('=', TK_NE)}, 1);
    add_state(S_19, (transition[]){f('@', S_20)}, 1);
    add_state(S_20, (transition[]){f('@', TK_OR)}, 1);
    add_state(S_22, (transition[]){f('&', S_23)}, 1);
    add_state(S_23, (transition[]){f('&', TK_AND)}, 1);
    add_state(S_25, aToZ(S_26), 26);
    add_state(S_26, aToZ(S_26), 26);
    add_state(S_26, theta44(TK_RUID), theta_size - 9);
    add_state(S_29, (transition[]){f('=', TK_GE)}, 1);
    add_state(S_29, theta('=', TK_GT), theta_size);
    add_state(S_32, (transition[]){f('=', TK_LE), f('-', S_35)}, 2);
    add_state(S_32, theta32(TK_LT_1), theta_size - 1);
    add_state(S_35, (transition[]){f('-', S_37)}, 1);
    add_state(S_35, theta('-', TK_LT_2), theta_size);
    add_state(S_37, (transition[]){f('-', TK_ASSIGNOP)}, 1);
    add_state(S_40, AToZ(S_41), 52);
    add_state(S_41, AToZ(S_41), 52);
    add_state(S_41, aToZ(S_41), 26);
    add_state(S_41, zeroToNine(S_42), 10);
    add_state(S_41, theta41(S_43), total_size - 26 - 26 - 10);
    add_state(S_42, theta42(S_43), theta_size - 9);
    add_state(S_42, zeroToNine(S_42), 10);
    add_state(S_44, aToZ(S_44), 26);
    add_state(S_44, theta44(S_45), theta_size - 25);
    add_state(S_46, aToZ(S_44), 26);
    add_state(S_46, twoToSeven(S_47), 6);
    add_state(S_47, bToD(S_47), 3);
    add_state(S_47, theta47(S_49), total_size - 6 - 3);
    add_state(S_47, twoToSeven(S_48), 6);
    add_state(S_48, theta48(TK_ID), theta_size - 5);
    add_state(S_48, twoToSeven(S_48), 6);
    add_state(S_50, (transition[]){f('.', S_52)}, 1);
    add_state(S_50, theta50(TK_NUM_1), theta_size - 10);
    add_state(S_50, zeroToNine(S_50), 10);
    add_state(S_52, theta52(S_61), theta_size - 9);
    add_state(S_52, zeroToNine(S_53), 10);
    add_state(S_53, zeroToNine(S_54), 10);
    add_state(S_54, (transition[]){f('E', S_56)}, 1);
    add_state(S_54, theta('E', TK_NUM_2), theta_size);
    add_state(S_56, (transition[]){f('+', S_59), f('-', S_59)}, 2);
    add_state(S_56, zeroToNine(S_57), 10);
    add_state(S_57, zeroToNine(TK_RNUM), 10);
    add_state(S_59, zeroToNine(S_57), 10);

    // look_up_table
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
    for (int i = 0; i < MAX_STATES; i++)
    {
        printf("State %d\n", i);
        for (int j = 0; j < states[i].length; j++)
        {
            printf("  %c\n", states[i].transitions[j]->next_char);
        }
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
            fprintf(new_fp, "%d ", info->tokens[i]);
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
    tokens->tokens = (int *)malloc(MAX_BUFFER_SIZE * sizeof(int));
    tokens->token_count = 0;

    char keyword[15];

    printf("%s\n", buffer->secondary_buffer);

    printf("%s\n", buffer->primary_buffer);

    int till = 0;

    int is_filled = buffer->secondary_buffer_index > 0;

    int token_len = 0;
    int token_count = 0;

    while (till < buffer->secondary_buffer_index)
    {

        curr_state = get_next_state(curr_state, buffer->secondary_buffer[till]);
        printf("%d %c he\n", curr_state->state_id, buffer->secondary_buffer[till]);
        till -= curr_state->retract_count;
        if (curr_state->is_final_state)
        {
            if (curr_state->state_id == S_43 || curr_state->state_id == S_45)
            {
                memset(keyword, '\0', 15);
                strncpy(keyword, buffer->secondary_buffer + till - token_len, token_len);
                curr_state = &states[search(look_up_table, keyword)];
            }
            tokens->tokens[tokens->token_count] = curr_state->state_id;
            tokens->token_count++;
            curr_state = &states[START];
            token_len = 0;
        }
        token_len++;
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
        // printf("%d %c \n", curr_state->state_id, buffer->primary_buffer[buffer->primary_buffer_index]);
        if (buffer->primary_buffer[buffer->primary_buffer_index] == '\n')
        {
            line_count++;
        }
        till -= curr_state->retract_count;
        if (curr_state->is_final_state)
        {
            if (curr_state->state_id == S_43 || curr_state->state_id == S_45)
            {
                memset(keyword, '\0', 15);
                strncpy(keyword, buffer->primary_buffer + buffer->primary_buffer_index - token_len, token_len);
                // curr_state = &states[search(look_up_table, keyword)];
                // printf("%d Word ID\n", search(look_up_table, keyword));
                printf("%s Word\n", keyword);
            }
            tokens->tokens[tokens->token_count] = curr_state->state_id;
            tokens->token_count++;
            curr_state = &states[START];
            token_len = 0;
        }
        token_len++;
        buffer->primary_buffer_index++;
        // prev_state = curr_state;
    }
    if (curr_state == &states[S_0])
    {
        strncpy(buffer->secondary_buffer, "%\0", 1);
        buffer->secondary_buffer_index = 1;
    }
    else if (curr_state != &states[START])
    {
        strncpy(buffer->secondary_buffer, buffer->primary_buffer + MAX_BUFFER_SIZE - 1 - token_len, token_len);
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

    for (int i = 0; i < current_state->length; i++)
    {
        if (current_state->transitions[i]->next_char == next_char)
        {
            return current_state->transitions[i]->next_state;
        }
    }
    return &states[TK_INVALID];
}

int main()
{
    initialize_states();
    FILE *fp = fopen("t1.txt", "r");
    FILE *new_fp = getStream(fp);
    fclose(new_fp);
    return 0;
}