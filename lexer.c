#include "lexerDef.h"

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
    for (int i = 0; i < size; i++)
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

transition *theta41(state_id next_state)
{
    // total - (a-z) - (A-Z) - (0-9)
    int size = sizeof(alphabets) / sizeof(char) - 26 - 26 - 10;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < size; i++)
    {

        if ((alphabets[i] >= 'a' && alphabets[i] <= 'z') || (alphabets[i] >= 'A' && alphabets[i] <= 'Z') || (alphabets[i] >= '0' && alphabets[i] <= '9'))
            continue;
        transitions[j++] = f(alphabets[i], next_state);
    }
    return transitions;
}

transition *theta47(state_id next_state)
{
    // total - (b-d) - (2-7)
    int size = sizeof(alphabets) / sizeof(char) - 3 - 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if ((alphabets[i] >= 'b' && alphabets[i] <= 'd') || (alphabets[i] >= '2' && alphabets[i] <= '7'))
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
    }
    int theta_size = sizeof(alphabets) / sizeof(char) - 1;
    int total_size = theta_size + 1;

    add_state(START, (transition[]){f('%', S_0), f(' ', START), f('@', S_19), f('&', S_22), f('#', S_25), f('*', TK_MUL), f('>', S_29), f('<', S_32), f('/', TK_DIV), f('\t', START), f('\n', START), f('~', TK_NOT), f('[', TK_SQL), f(']', TK_SQR), f(',', TK_COMMA), f(';', TK_SEM), f(':', TK_COLON), f('.', TK_DOT), f('(', TK_OP), f(')', TK_CL), f('=', TK_EQ), f('+', TK_PLUS), f('-', TK_MINUS), f('!', S_17)}, 24);
    add_state(START, bToD(S_46), 3);
    add_state(START, zeroToNine(S_50), 10);
    add_state(START, aToZExceptBToD(S_44), 23);
    add_state(S_0, theta('\n', S_0), theta_size);
    add_state(S_0, (transition[]){f('\n', S_1)}, 1);

    add_state(S_13, (transition[]){f('=', TK_EQ)}, 1);
    add_state(S_17, (transition[]){f('=', TK_NE)}, 1);
    add_state(S_19, (transition[]){f('@', S_20)}, 1);
    add_state(S_23, (transition[]){f('&', TK_AND)}, 1);
    add_state(S_25, aToZ(S_26), 26);
    add_state(S_29, theta('=', TK_GT), theta_size);
    add_state(S_29, (transition[]){f('=', TK_GE)}, 1);
    add_state(S_35, theta('-', TK_LT), theta_size);
    add_state(S_35, (transition[]){f('-', S_37)}, 1);
    add_state(S_37, (transition[]){f('-', TK_ASSIGNOP)}, 1);
    add_state(S_41, AToZ(S_41), 26);
    add_state(S_41, aToZ(S_41), 26);
    add_state(S_41, zeroToNine(S_42), 10);
    add_state(S_41, theta41(S_41), total_size - 26 - 26 - 10);
    add_state(S_47, twoToSeven(S_48), 6);
    add_state(S_47, bToD(S_47), 3);
    add_state(S_47, theta47(S_49), total_size - 6 - 3);
    add_state(S_53, zeroToNine(S_54), 10);
    add_state(S_57, zeroToNine(TK_RNUM), 10);
    add_state(S_59, zeroToNine(S_57), 10);

    // TODO: Even starting states
    add_state(S_20, (transition[]){f('@', TK_OR)}, 1);
    add_state(S_22, (transition[]){f('&', S_23)}, 1);
    add_state(S_26, theta('$', TK_RUID), theta_size + 1);
    add_state(S_26, aToZ(S_26), 26);
    add_state(S_32, theta('$', TK_LT), theta_size + 1);
    add_state(S_32, (transition[]){f('=', TK_LE), f('-', S_35)}, 1);
    add_state(S_40, AToZ(41), 52);
    add_state(S_42, zeroToNine(S_42), 10);
    add_state(S_42, theta('$', S_43), theta_size + 1);
    add_state(S_44, aToZ(S_44), 26);
    add_state(S_44, theta('$', S_45), theta_size + 1);
    add_state(S_46, twoToSeven(S_47), 26);
    add_state(S_46, aToZ(S_44), 26);
    add_state(S_48, twoToSeven(S_48), 6);
    add_state(S_48, theta('$', TK_ID), theta_size + 1);
    add_state(S_50, zeroToNine(S_50), 10);
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
    // make a new .salad file
    // get the file name of fp
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
    // read from secondary buffer first if it is not empty

    tokenInfo tokens = (tokenInfo)malloc(sizeof(TokenInfo));
    tokens->tokens = (int *)malloc(MAX_BUFFER_SIZE * sizeof(int));
    tokens->token_count = 0;

    while (buffer->secondary_buffer_index > 0)
    {
        curr_state = get_next_state(curr_state, buffer->secondary_buffer[buffer->secondary_buffer_index]);
        buffer->secondary_buffer_index--;
    }

    // read from primary buffer
    int token_len = 0;
    int token_count = 0;
    while (buffer->primary_buffer_index < MAX_BUFFER_SIZE)
    {
        curr_state = get_next_state(curr_state, buffer->primary_buffer[buffer->primary_buffer_index]);
        if (buffer->primary_buffer[buffer->primary_buffer_index] == '\n')
        {
            line_count++;
        }
        if (curr_state == &states[START] && prev_state != NULL)
        {
            tokens->tokens[tokens->token_count] = prev_state->state_id;
            tokens->token_count++;
        }
        token_len++;
        buffer->primary_buffer_index++;
        prev_state = curr_state;
    }
    if (curr_state != &states[START])
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
}