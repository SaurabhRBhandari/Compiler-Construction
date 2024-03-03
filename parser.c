#include "parserDef.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX '$'
#define INT_MIN -21435
#define EPSILON '?'
FirstAndFollow ComputeFirstAndFollowSets(grammer G)
{
    FirstAndFollow F;
    F.no_of_terminals = G.no_of_terminals;
    F.no_of_variables = G.no_of_variables;
    for (int i = 0; i < G.no_of_variables; i++)
    {
        F.start_variable[i] = G.start_variable[i];
        F.elements[i].no_of_first = 0;
        F.elements[i].no_of_follow = 0;
    }
    for (int i = 0; i < G.no_of_terminals; i++)
    {
        F.terminals[i] = G.terminals[i];
    }

    // Compute First Sets
    bool computed[G.no_of_variables];
    for (int i = 0; i < G.no_of_variables; i++)
    {
        computed[i] = false;
    }
    for (int i = 0; i < G.no_of_variables;)
    {
        if (computed[i] == false)
        {
            int queue[G.no_of_variables];
            int front = 0;
            int rear = 0;
            queue[rear] = i;
            rear++;
            while (front < rear)
            {
                int current = queue[front];
                front++;
                variable *v = G.variables[current];
                bool is_computed = true;
                while (v != NULL)
                {
                    if (v->no_of_tokens > 0)
                    {
                        int k = 0;
                        bool is_epsilon = true;
                        while (k < v->no_of_tokens && is_epsilon == true)
                        {
                            if (v->tokens[k]->is_terminal == 1)
                            {
                                break;
                            }
                            else
                            {
                                if (computed[v->tokens[k]->name] == false)
                                {
                                    queue[rear] = v->tokens[k]->name;
                                    rear++;
                                    is_computed = false;
                                }
                                else
                                {
                                    is_epsilon = false;
                                    for (int l = 0; l < F.elements[v->tokens[k]->name].no_of_first; l++)
                                    {
                                        if (F.elements[v->tokens[k]->name].first[l] == EPSILON)
                                        {
                                            is_epsilon = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            k++;
                        }
                    }
                    v = v->next;
                }
                if (is_computed == true)
                {
                    variable *v = G.variables[current];
                    while (v != NULL)
                    {
                        if (v->no_of_tokens > 0)
                        {
                            int k = 0;
                            bool is_epsilon = true;
                            while (k < v->no_of_tokens && is_epsilon == true)
                            {
                                if (v->tokens[k]->is_terminal == 1)
                                {
                                    bool is_present = false;
                                    for (int l = 0; l < F.elements[current].no_of_first; l++)
                                    {
                                        if (F.elements[current].first[l] == v->tokens[k]->name)
                                        {
                                            is_present = true;
                                            break;
                                        }
                                    }
                                    if (is_present == false)
                                    {
                                        F.elements[current].first[F.elements[current].no_of_first] = v->tokens[k]->name;
                                        F.elements[current].first_rule[F.elements[current].no_of_first] = v->rule_no;
                                        F.elements[current].no_of_first++;
                                    }
                                    is_epsilon = false;
                                }
                                else
                                {
                                    is_epsilon = false;
                                    for (int l = 0; l < F.elements[v->tokens[k]->name].no_of_first; l++)
                                    {
                                        if (F.elements[v->tokens[k]->name].first[l] == EPSILON)
                                        {
                                            is_epsilon = true;
                                            continue;
                                        }
                                        bool is_present = false;
                                        for (int r = 0; r < F.elements[current].no_of_first; r++)
                                        {
                                            if (F.elements[current].first[r] == F.elements[v->tokens[k]->name].first[l])
                                            {
                                                is_present = true;
                                                break;
                                            }
                                        }
                                        if (is_present == false)
                                        {
                                            F.elements[current].first[F.elements[current].no_of_first] = F.elements[v->tokens[k]->name].first[l];
                                            F.elements[current].first_rule[F.elements[current].no_of_first] = F.elements[v->tokens[k]->name].first_rule[l];
                                            F.elements[current].no_of_first++;
                                        }
                                    }
                                }
                                k++;
                            }
                            if (is_epsilon == true)
                            {
                                bool is_present = false;
                                for (int l = 0; l < F.elements[current].no_of_first; l++)
                                {
                                    if (F.elements[current].first[l] == EPSILON)
                                    {
                                        is_present = true;
                                        break;
                                    }
                                }
                                if (is_present == false)
                                {
                                    F.elements[current].first[F.elements[current].no_of_first] = EPSILON;
                                    F.elements[current].first_rule[F.elements[current].no_of_first] = v->rule_no;
                                    F.elements[current].no_of_first++;
                                }
                            }
                        }
                        v = v->next;
                    }
                    computed[current] = true;
                }
            }
        }
        else
        {
            i++;
        }
    }

    // compute follow sets
    // Assumption 0 is the start variable and therefore adding $ in its follow set represeneted by INT_MAX
    F.elements[0].follow[F.elements[0].no_of_follow] = INT_MAX;
    F.elements[0].follow_rule[F.elements[0].no_of_follow] = 0;
    F.elements[0].no_of_follow++;
    for (int i = 0; i < G.no_of_variables; i++)
    {
        // iterate through all the starting variables
        variable *v = G.variables[i];
        while (v != NULL)
        {
            // iterate through all the rules of the variable
            if (v->no_of_tokens > 0)
            {
                for (int k = 0; k < v->no_of_tokens; k++)
                {
                    // iterate through all the tokens of the rule
                    if (v->tokens[k]->is_terminal == 0)
                    {
                        // if the token is a variable
                        int c = -2;
                        for (int i = 0; i < F.no_of_terminals; i++)
                        {
                            if (F.start_variable[i] == v->tokens[k]->name)
                            {
                                c = i;
                                break;
                            }
                        }
                        if (k < v->no_of_tokens - 1)
                        {
                            // if the token is not the last token of the rule
                            if (v->tokens[k + 1]->is_terminal == 1)
                            {
                                // if the next token is a terminal
                                // check if the terminal is already present in the follow set of the current token
                                bool is_present = false;
                                for (int l = 0; l < F.elements[c].no_of_follow; l++)
                                {
                                    if (F.elements[c].follow[l] == v->tokens[k + 1]->name)
                                    {
                                        is_present = true;
                                        break;
                                    }
                                }
                                // if the terminal is not present in the follow set of the current token then add it to the follow set
                                if (is_present == false)
                                {
                                    F.elements[c].follow[F.elements[c].no_of_follow] = v->tokens[k + 1]->name;
                                    F.elements[c].follow_rule[F.elements[c].no_of_follow] = v->rule_no;
                                    F.elements[c].no_of_follow++;
                                }
                            }
                            else
                            {
                                // if the next token is a variable
                                int l = k + 1;
                                bool is_epsilon = true;
                                while (l < v->no_of_tokens && is_epsilon == true)
                                {
                                    // iterate through all the tokens after the token k
                                    if (v->tokens[l]->is_terminal == 1)
                                    {
                                        // if the token is a terminal
                                        // check if the terminal is already present in the first set of the current token
                                        bool is_present = false;
                                        is_epsilon = false;
                                        for (int r = 0; r < F.elements[c].no_of_first; r++)
                                        {
                                            if (F.elements[c].first[r] == v->tokens[l]->name)
                                            {
                                                is_present = true;
                                                break;
                                            }
                                        }
                                        // if the terminal is not present in the first set of the next token then add it to the follow set of the current token
                                        if (is_present == false)
                                        {
                                            F.elements[c].follow[F.elements[c].no_of_follow] = v->tokens[l]->name;
                                            F.elements[c].follow_rule[F.elements[c].no_of_follow] = v->rule_no;
                                            F.elements[c].no_of_follow++;
                                        }
                                        is_epsilon = false;
                                    }
                                    else
                                    {
                                        // if the token is a variable
                                        int lindex = -2;
                                        for (int i = 0; i < F.no_of_terminals; i++)
                                        {
                                            if (F.start_variable[i] == v->tokens[l]->name)
                                            {
                                                lindex = i;
                                                break;
                                            }
                                        }
                                        is_epsilon = false;
                                        for (int r = 0; r < F.elements[lindex].no_of_first; r++)
                                        {
                                            if (F.elements[lindex].first[r] == EPSILON)
                                            {
                                                is_epsilon = true;
                                                continue;
                                            }
                                            bool is_present = false;
                                            for (int m = 0; m < F.elements[c].no_of_follow; m++)
                                            {
                                                if (F.elements[c].follow[m] == F.elements[lindex].first[r])
                                                {
                                                    is_present = true;
                                                    break;
                                                }
                                            }
                                            if (is_present == false)
                                            {
                                                F.elements[c].follow[F.elements[c].no_of_follow] = F.elements[lindex].first[r];
                                                F.elements[c].follow_rule[F.elements[c].no_of_follow] = v->rule_no;
                                                F.elements[c].no_of_follow++;
                                            }
                                        }
                                    }
                                    l++;
                                }
                                // if is_epsilon is true then add the lhs variable to the follow set of the current token which will be computed later
                                if (is_epsilon == true)
                                {
                                    bool is_present = false;
                                    for (int r = 0; r < F.elements[c].no_of_follow; r++)
                                    {
                                        if (F.elements[c].follow[r] == G.start_variable[i])
                                        {
                                            is_present = true;
                                            break;
                                        }
                                    }
                                    if (is_present == false)
                                    {
                                        F.elements[c].follow[F.elements[c].no_of_follow] = G.start_variable[i];
                                        F.elements[c].follow_rule[F.elements[c].no_of_follow] = v->rule_no;
                                        F.elements[c].no_of_follow++;
                                    }
                                }
                            }
                        }
                        // if the token is the last token of the rule
                        else
                        {
                            bool is_present = false;
                            for (int l = 0; l < F.elements[c].no_of_follow; l++)
                            {
                                if (F.elements[c].follow[l] == G.start_variable[i])
                                {
                                    is_present = true;
                                    break;
                                }
                            }
                            if (is_present == false)
                            {
                                F.elements[c].follow[F.elements[c].no_of_follow] = G.start_variable[i];
                                F.elements[c].follow_rule[F.elements[c].no_of_follow] = v->rule_no;
                                F.elements[c].no_of_follow++;
                            }
                        }
                    }
                }
            }
            v = v->next;
        }
    }
    // complete follow sets by adding the follow sets of non-terminal to the follow sets of the variables
    //  make a list of non-terminals
    bool non_terminals[F.no_of_terminals];
    for (int i = 0; i < F.no_of_terminals; i++)
    {
        non_terminals[i] = false;
    }
    for (int i = 0; i < G.no_of_variables; i++)
    {
        non_terminals[G.start_variable[i]] = true;
    }
    // iterate through all follow sets
    for (int i = 0; i < F.no_of_variables; i++)
    {
        if (computed[F.start_variable[i]] == false)
        {
            // if the follow set is not computed iterate through the follow set and check if there is a non-terminal
            for (int j = 0; j < F.elements[i].no_of_follow; j++)
            {
                if (F.elements[i].follow[j] != INT_MAX && non_terminals[F.elements[i].follow[j]] == true)
                {
                    // if there is a non-terminal then add the follow set of the non-terminal to the follow set of the current token
                    printf("%d", F.elements[i].follow[j]);
                    for (int k = 0; k < F.elements[F.elements[i].follow[j]].no_of_follow; k++)
                    {
                        bool is_present = false;
                        for (int l = 0; l < F.elements[i].no_of_follow; l++)
                        {
                            if (F.elements[i].follow[l] == F.elements[F.elements[i].follow[j]].follow[k])
                            {
                                is_present = true;
                                break;
                            }
                        }
                        if (is_present == false)
                        {
                            F.elements[i].follow[F.elements[i].no_of_follow] = F.elements[F.elements[i].follow[j]].follow[k];
                            F.elements[i].follow_rule[F.elements[i].no_of_follow] = F.elements[F.elements[i].follow[j]].follow_rule[k];
                            F.elements[i].no_of_follow++;
                        }
                    }
                }
            }
            computed[F.start_variable[i]] = true;
        }
    }
    // iterate through all the follow sets
    // print non_terminals
    for (int i = 0; i < F.no_of_variables; i++)
    {
        // iterate through the follow set to check if a non_terminal is present
        for (int j = 0; j < F.elements[i].no_of_follow; j++)
        {
            if (F.elements[i].follow[j] == INT_MAX)
                continue;
            if (non_terminals[F.elements[i].follow[j]] == true)
            {
                // if a non-terminal is present , remove it from the follow set
                for (int k = j; k < F.elements[i].no_of_follow - 1; k++)
                {
                    F.elements[i].follow[k] = F.elements[i].follow[k + 1];
                    F.elements[i].follow_rule[k] = F.elements[i].follow_rule[k + 1];
                }
                F.elements[i].no_of_follow--;
            }
        }
    }
    return F;
}


bool createParseTable(FirstAndFollow F, table *T)
{
    // Find number of terminal tokens and variables
    T->no_of_rows = F.no_of_variables;
    T->no_of_columns = F.no_of_terminals + 1;
    // initialize the rows
    for (int i = 0; i < F.no_of_variables; i++)
    {
        T->row[i] = F.start_variable[i];
    }
    // initialize the columns
    for (int i = 0; i < F.no_of_terminals; i++)
    {
        T->column[i] = F.terminals[i];
    }
    T->column[F.no_of_terminals] = INT_MAX;
    // initialize the tables
    for (int i = 0; i < F.no_of_variables; i++)
    {
        for (int j = 0; j < F.no_of_terminals + 1; j++)
        {
            T->table[i][j] = INT_MIN;
        }
    }
    // TODO: if map possible in C then can decrease TC by factor of n
    bool is_LL1 = true;
    // iterate through all the variables
    for (int i = 0; i < F.no_of_variables; i++)
    {
        // iterate through the first set of the variable
        for (int j = 0; j < F.elements[i].no_of_first; j++)
        {
            // if the first set contains epsilon then add the follow set of the variable to the parse table
            if (F.elements[i].first[j] == EPSILON)
            {
                for (int k = 0; k < F.elements[i].no_of_follow; k++)
                {
                    int c = -2;
                    for (int z = 0; z < F.no_of_terminals; z++)
                    {
                        if (F.elements[i].follow[k] == T->column[z])
                        {
                            c = z;
                            break;
                        }
                    }
                    if (T->table[i][c] != INT_MIN)
                    {
                        is_LL1 = false;
                    }
                    T->table[i][c] = F.elements[i].first_rule[j];
                }
            }
            else
            {
                // if the first set contains a terminal then add the rule to the parse table
                if (T->table[i][F.elements[i].first[j] - 1] != INT_MIN)
                {
                    is_LL1 = false;
                }
                int c = -2;
                for (int z = 0; z < F.no_of_terminals; z++)
                {
                    if (F.elements[i].first[j] == T->column[z])
                    {
                        c = z;
                        break;
                    }
                }
                T->table[i][c] = F.elements[i].first_rule[j];
            }
        }
    }
    return is_LL1;
}


void printParseTree(table T, FirstAndFollow F, grammer G, char *input, int n)
{
    //parse the input using the parse table and print the parse tree
    //if the input is not valid then print "Input is not valid"

    //initialize the stack
    char stack[100];
    int top = -1;
    stack[++top] = INT_MAX;
    stack[++top] = G.start_variable[0];
    int i = 0;
    while (i < n)
    {
        int c = -2;
        for (int j = 0; j < F.no_of_terminals; j++)
        {
            if (input[i] == T.column[j])
            {
                c = j;
                break;
            }
        }
        if (c == -2)
        {
            printf("Input is not valid\n");
            return;
        }
        int r = -2;
        for (int j = 0; j < F.no_of_variables; j++)
        {
            if (stack[top] == T.row[j])
            {
                r = j;
                break;
            }
        }
        if (r == -2)
        {
            printf("Input is not valid\n");
            return;
        }
        // printf("%c %c %d %d\n",stack[top],input[i],r,c);
        if (T.table[r][c] == INT_MIN)
        {
            printf("Input is not valid\n");
            return;
        }
        variable *v = G.variables[r];
        while (v != NULL)
        {
            if (v->rule_no == T.table[r][c])
            {
                top--;
                //push the tokens of the rule to the stack
                for (int j = v->no_of_tokens - 1; j >= 0; j--)
                {
                        top+=1;
                        stack[top] = v->tokens[j]->name;
                }
                break;
            }
            v = v->next;
        }
        while(stack[top]==input[i]||stack[top]==EPSILON)
        {
            if(stack[top]!=EPSILON) i++;
            top--;
        }
    }
    if (top == 0 && stack[top] == INT_MAX)
    {
        printf("Input is valid\n");
    }
    else
    {
        printf("Input is not valid\n");
    }
    return;

}

grammer grammyInit(int no_of_variables,int no_of_terminals){
    grammer G;
    G.no_of_variables = 0;
    G.no_of_terminals = 0;
    G.no_of_rules = 0;
    return G;
}

void grammySays(grammer *G,int start_variable,int no_of_tokens,token *tokens){
    //finding the index of the lhs variable
    int index = -2;
    for(int i=0;i<G->no_of_variables;i++){
        index = i;
        if(G->start_variable[i] == start_variable){
            break;
        }
    }
    //debugging
    if(index==G->no_of_variables){
        G->start_variable[index] = start_variable;
        G->no_of_variables++;
    }
    //iterate through the rules of the variable to reach the end of the linked list
    variable *v = G->variables[index];
    while(v!=NULL) v = v->next;
    v = (variable *)malloc(sizeof(variable));
    v->no_of_tokens = no_of_tokens;
    v->rule_no = G->no_of_rules+1;

    for(int i=0;i<no_of_tokens;i++){

        v->tokens[i] = (token *)malloc(sizeof(token));
        v->tokens[i]->name = tokens[i].name;
        v->tokens[i]->is_terminal = tokens[i].is_terminal;
        if(tokens[i].is_terminal==0){
            int index = -2;
            for(int j=0;j<G->no_of_variables;j++){
                index = j;
                if(G->start_variable[j] == tokens[i].name){
                    break;
                }
            }
            if(index==G->no_of_variables){
                G->start_variable[index] = tokens[i].name;
                G->no_of_variables++;
            }
        }
        else if (tokens[i].is_terminal==1){
            int index = -2;
            for(int j=0;j<G->no_of_terminals;j++){
                index = j;
                if(G->terminals[j] == tokens[i].name){
                    break;
                }
            }
            if(index==G->no_of_terminals){
                G->terminals[index] = tokens[i].name;
                G->no_of_terminals++;
            }
        }
    }
    v->next = NULL;
    G->no_of_rules++;
}
int main()
{
    grammer G;
    G.no_of_variables = 3;
    G.no_of_terminals = 4;
    G.start_variable[0] = 'S';
    G.start_variable[1] = 'A';
    G.start_variable[2] = 'B';
    G.terminals[0] = 'a';
    G.terminals[1] = 'b';
    G.terminals[2] = 'c';
    G.terminals[3] = 'd';
    G.variables[0] = (variable *)malloc(sizeof(variable));
    G.variables[0]->no_of_tokens = 4;
    G.variables[0]->rule_no = 1;
    G.variables[0]->tokens[0] = (token *)malloc(sizeof(token));
    G.variables[0]->tokens[0]->name = 'a';
    G.variables[0]->tokens[0]->is_terminal = 1;
    G.variables[0]->tokens[1] = (token *)malloc(sizeof(token));
    G.variables[0]->tokens[1]->name = 'A';
    G.variables[0]->tokens[1]->is_terminal = 0;
    G.variables[0]->tokens[2] = (token *)malloc(sizeof(token));
    G.variables[0]->tokens[2]->name = 'B';
    G.variables[0]->tokens[2]->is_terminal = 0;
    G.variables[0]->tokens[3] = (token *)malloc(sizeof(token));
    G.variables[0]->tokens[3]->name = 'b';
    G.variables[0]->tokens[3]->is_terminal = 1;


    G.variables[0]->next = NULL;
    G.variables[1] = (variable *)malloc(sizeof(variable));
    G.variables[1]->no_of_tokens = 1;
    G.variables[1]->rule_no = 2;
    G.variables[1]->tokens[0] = (token *)malloc(sizeof(token));
    G.variables[1]->tokens[0]->name = 'c';
    G.variables[1]->tokens[0]->is_terminal = 1;
    G.variables[1]->next = (variable *)malloc(sizeof(variable));
    G.variables[1]->next->no_of_tokens = 1;
    G.variables[1]->next->rule_no = 3;
    G.variables[1]->next->tokens[0] = (token *)malloc(sizeof(token));
    G.variables[1]->next->tokens[0]->name = EPSILON;
    G.variables[1]->next->tokens[0]->is_terminal = 1;
    G.variables[1]->next->next = NULL;
    G.variables[2] = (variable *)malloc(sizeof(variable));
    G.variables[2]->no_of_tokens = 1;
    G.variables[2]->rule_no = 4;
    G.variables[2]->tokens[0] = (token *)malloc(sizeof(token));
    G.variables[2]->tokens[0]->name = 'd';
    G.variables[2]->tokens[0]->is_terminal = 1;
    G.variables[2]->next = (variable *)malloc(sizeof(variable));
    G.variables[2]->next->no_of_tokens = 1;
    G.variables[2]->next->rule_no = 5;
    G.variables[2]->next->tokens[0] = (token *)malloc(sizeof(token));
    G.variables[2]->next->tokens[0]->name =  EPSILON;
    G.variables[2]->next->tokens[0]->is_terminal = 1;
    G.variables[2]->next->next = NULL;
    FirstAndFollow F = ComputeFirstAndFollowSets(G);
    // Print First and Follow Sets
    for (int i = 0; i < F.no_of_variables; i++)
    {
        printf("First Set of %c: ", F.start_variable[i]);
        for (int j = 0; j < F.elements[i].no_of_first; j++)
        {
            printf("%c ", F.elements[i].first[j]);
        }
        printf("\n");
    }
    for (int i = 0; i < F.no_of_variables; i++)
    {
        printf("Follow Set of %c: ", F.start_variable[i]);
        for (int j = 0; j < F.elements[i].no_of_follow; j++)
        {
            printf("%c ", F.elements[i].follow[j]);
        }
        printf("\n");
    }
    table T;
    bool is_LL1 = createParseTable(F, &T);
    // Print Parse Table
    printf("0 ");
    for (int i = 0; i < T.no_of_columns; i++)
    {
        printf("%c ", T.column[i]);
    }
    printf("\n");
    for (int i = 0; i < T.no_of_rows; i++)
    {
        printf("%c ", T.row[i]);
        for (int j = 0; j < T.no_of_columns; j++)
        {
            if(T.table[i][j] == INT_MIN)
            {
                printf("- ");
            }
            else
            printf("%d ", T.table[i][j]);
        }
        printf("\n");
    }
    //print all the rules of the grammer in the form of a table with the rule number and the rule
    for (int i = 0; i < G.no_of_variables; i++)
    {
        variable *v = G.variables[i];
        while (v != NULL)
        {
            printf("%d: %c -> ", v->rule_no, G.start_variable[i]);
            for (int j = 0; j < v->no_of_tokens; j++)
            {
                printf("%c ", v->tokens[j]->name);
            }
            printf("\n");
            v = v->next;
        }
    }
    // print the parse tree
    char input[4] = {'a', 'c','d' ,'b'};
    printParseTree(T, F, G, input, 4);
    return 0;
}