#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
enum token {TK_INVALID,TK_ASSIGNOP, TK_COMMENT, TK_FIELDID, TK_ID,TK_NUM, TK_RNUM, TK_RNUM, TK_FUNID, TK_RUID,TK_WITH ,TK_PARAMETERS ,TK_END ,TK_WHILE ,TK_UNION ,TK_ENDUNION ,TK_DEFINETYPE ,TK_AS ,TK_TYPE ,TK_MAIN ,TK_GLOBAL ,TK_PARAMETER ,TK_LIST,TK_SQL,TK_SQR,TK_INPUT,TK_OUTPUT,TK_INT,TK_REAL,TK_COMMA,TK_SEM,TK_COLON,TK_DOT,TK_ENDWHILE,TK_OP,TK_CL,TK_IF,TK_THEN,TK_ENDIF,TK_READ,TK_WRITE,TK_RETURN,TK_PLUS,TK_MINUS,TK_MUL,TK_DIV,TK_CALL,TK_RECORD,TK_ENDRECORD,TK_ELSE,TK_AND,TK_OR,TK_NOT,TK_LT,TK_LE,TK_EQ,TK_GT,TK_GE,TK_NE};
struct Veggie
{
    struct Veggie* characters[ALPHABET];
    int token;
};

struct Veggie *getSlice(void)
{
    struct Veggie* newSlice= NULL;
    newSlice = (struct Veggie*)malloc(sizeof(struct Veggie));
    if(newSlice)
    {
        int i;
        newSlice->token = TK_INVALID;

        for(i=0; i<ALPHABET; i++) newSlice->characters[i] = NULL;
    }

    return newSlice;
}

void insertSlice(struct Veggie* bowl, const char* ingredient,int Token){
    int nutrient,size = strlen(ingredient),index;
    struct Veggie *thisSlice = bowl;
    for(nutrient=0; nutrient<size;nutrient++){
        index = (int)ingredient[nutrient] - (int)'a';
        if(!thisSlice->characters[index])
            thisSlice->characters[index] = getSlice();
        
        thisSlice->token = Token;
    }
}

int tasteSlice(struct Veggie* bowl,const char* ingredient){
    int nutrient,size = strlen(ingredient),index;
    struct Veggie* thisSlice = bowl;
    for(nutrient =0; nutrient<size;nutrient++){
        index = (int)ingredient[nutrient] - (int)'a';
        if(!thisSlice->characters[index])
            return TK_INVALID; //Rotten Vegetable
        thisSlice = thisSlice->characters[index];
    }
    return thisSlice->token; //type of vegetable
}

