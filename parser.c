#include "parserDef.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

FirstAndFollow ComputeFirstAndFollowSets(grammer G){
    FirstAndFollow F;
    F.no_of_tokens = G.no_of_variables;
    for(int i=0;i<G.no_of_variables;i++){
        F.tokens[i] = G.start_variable[i];
        F.elements[i].no_of_first = 0;
        F.elements[i].no_of_follow = 0;
    }
    // Compute First Sets
    bool computed[G.no_of_variables];
    for(int i=0;i<G.no_of_variables;i++){
        computed[i] = false;
    }
    for(int i=0;i<G.no_of_variables;){
        if(computed[i]==false){
            int queue[G.no_of_variables];
            int front = 0;
            int rear = 0;
            queue[rear] = i;
            rear++;
            while(front<rear){
                int current=queue[front];
                front++;
                variable* v = G.variables[current];
                bool terminal=true;
                while(v!=NULL){
                    if(v->no_of_tokens>0){
                        if(G.variables[current]->tokens[0]->is_terminal==1){
                            continue;
                        }
                        else if(computed[G.variables[current]->tokens[0]->name]==true){
                            continue;
                        }
                        else{
                            terminal=false;
                            queue[rear] = G.variables[current]->tokens[0]->name;
                            rear++;
                        }
                    }
                    v=v->next;
                }
                if(terminal==true){
                    variable* v = G.variables[current];
                    while(v!=NULL){
                        if(v->no_of_tokens>0){
                            F.elements[i].first[F.elements[i].no_of_first] = v->tokens[0]->name;
                            F.elements[i].no_of_first++;
                        }
                        v=v->next;
                    }
                    computed[i]=true;
                }
            }

        }
        else{
            i++;
        }
    }
    return F;
}

int main(){
    grammer G;
    G.no_of_variables = 1;
    G.start_variable[0] = 0;
    G.variables[0] = (variable*)malloc(sizeof(variable));
    G.variables[0]->no_of_tokens = 1;
    G.variables[0]->rule_no = 0;
    G.variables[0]->tokens[0] = (token*)malloc(sizeof(token));
    G.variables[0]->tokens[0]->name = 0;
    G.variables[0]->tokens[0]->is_terminal = 1;
    G.variables[0]->next = NULL;
    FirstAndFollow F = ComputeFirstAndFollowSets(G);
    //Print First and Follow Sets
    for(int i=0;i<F.no_of_tokens;i++){
        printf("First Set of %d: ",F.tokens[i]);
        for(int j=0;j<F.elements[i].no_of_first;j++){
            printf("%d ",F.elements[i].first[j]);
        }
        printf("\n");
    }
    return 0;
}