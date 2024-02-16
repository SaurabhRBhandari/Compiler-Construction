#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 100

typedef struct token{
    int name;
    int is_terminal;
}token;

typedef struct variable variable;
typedef struct variable{
    int no_of_tokens;
    int rule_no;
    token* tokens[MAX_TOKENS];
    variable* next;
}variable;

typedef struct grammer{
    int no_of_variables;
    int start_variable[MAX_TOKENS];
    variable* variables[MAX_TOKENS];
}grammer;

typedef struct first_follow_element{
    int no_of_first;
    int no_of_follow;
    int first[MAX_TOKENS];
    int follow[MAX_TOKENS];
}first_follow_element;

typedef struct FirstAndFollow{
    int no_of_tokens;
    int tokens[MAX_TOKENS];
    first_follow_element elements[MAX_TOKENS];
}FirstAndFollow;


typedef struct parse_table{
    int no_of_rows;
    int no_of_columns;
    int row[MAX_TOKENS];
    int column[MAX_TOKENS];
    int table[MAX_TOKENS][MAX_TOKENS];
}parse_table;
