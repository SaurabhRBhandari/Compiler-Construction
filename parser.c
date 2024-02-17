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
                bool is_computed=true;
                while(v!=NULL){
                    if(v->no_of_tokens>0){
                        int k=0;
                        bool is_epsilon=true;
                        while(k<v->no_of_tokens && is_epsilon==true){
                            if(v->tokens[k]->is_terminal==1){
                                break;
                            }
                            else{
                                if(computed[v->tokens[k]->name]==false){
                                    queue[rear] = v->tokens[k]->name;
                                    rear++;
                                    is_computed=false;
                                }
                                else{
                                    is_epsilon=false;
                                    for(int l=0;l<F.elements[v->tokens[k]->name].no_of_first;l++){
                                        if(F.elements[v->tokens[k]->name].first[l]==-1){
                                            is_epsilon=true;
                                            break;
                                        }
                                    }                  
                                }
                            }
                            k++;
                        }
                    }
                    v=v->next;
                }
                if(is_computed==true){
                    variable* v = G.variables[current];
                    while(v!=NULL){                
                        if(v->no_of_tokens>0){
                            int k=0;
                            bool is_epsilon=true;
                            while(k<v->no_of_tokens && is_epsilon==true){
                                if(v->tokens[k]->is_terminal==1){
                                    bool is_present=false;
                                    for(int l=0;l<F.elements[current].no_of_first;l++){
                                        if(F.elements[current].first[l]==v->tokens[k]->name){
                                            is_present=true;
                                            break;
                                        }
                                    }
                                    if(is_present==false){
                                        F.elements[current].first[F.elements[current].no_of_first] = v->tokens[k]->name;
                                        F.elements[current].no_of_first++;
                                    }
                                    is_epsilon=false;
                                }
                                else{
                                    is_epsilon=false;
                                    for(int l=0;l<F.elements[v->tokens[k]->name].no_of_first;l++){
                                        if(F.elements[v->tokens[k]->name].first[l]==-1){
                                            is_epsilon=true;
                                            continue;
                                        }
                                        bool is_present=false;
                                        for(int r=0;r<F.elements[current].no_of_first;r++){
                                            if(F.elements[current].first[r]==F.elements[v->tokens[k]->name].first[l]){
                                                is_present=true;
                                                break;
                                            }
                                        }
                                        if(is_present==false){
                                            F.elements[current].first[F.elements[current].no_of_first] = F.elements[v->tokens[k]->name].first[l];
                                            F.elements[current].no_of_first++;
                                        }
                                    }
                                }
                                k++;
                            }
                            if(is_epsilon==true){
                                bool is_present=false;
                                for(int l=0;l<F.elements[current].no_of_first;l++){
                                    if(F.elements[current].first[l]==-1){
                                        is_present=true;
                                        break;
                                    }
                                }
                                if(is_present==false){
                                    F.elements[current].first[F.elements[current].no_of_first] = -1;
                                    F.elements[current].no_of_first++;
                                }
                            }
                        }
                        v=v->next;
                    }
                    computed[current]=true;
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
    G.no_of_variables = 3;
    G.start_variable[0] = 0;
    G.start_variable[1] = 1;
    G.start_variable[2] = 2;
    G.variables[0] = (variable*)malloc(sizeof(variable));
    G.variables[0]->no_of_tokens = 2;
    G.variables[0]->rule_no = 1;
    G.variables[0]->tokens[0] = (token*)malloc(sizeof(token));
    G.variables[0]->tokens[0]->name = 1;
    G.variables[0]->tokens[0]->is_terminal = 0;
    G.variables[0]->tokens[1] = (token*)malloc(sizeof(token));
    G.variables[0]->tokens[1]->name = 5;
    G.variables[0]->tokens[1]->is_terminal = 1;
    G.variables[0]->next = NULL;
    G.variables[1] = (variable*)malloc(sizeof(variable));
    G.variables[1]->no_of_tokens = 1;
    G.variables[1]->rule_no = 3;
    G.variables[1]->tokens[0] = (token*)malloc(sizeof(token));
    G.variables[1]->tokens[0]->name = -1;
    G.variables[1]->tokens[0]->is_terminal = 1;
    G.variables[1]->next = (variable*)malloc(sizeof(variable));
    G.variables[1]->next->no_of_tokens = 1;
    G.variables[1]->next->rule_no = 4;
    G.variables[1]->next->tokens[0] = (token*)malloc(sizeof(token));
    G.variables[1]->next->tokens[0]->name = 3;
    G.variables[1]->next->tokens[0]->is_terminal = 1;
    G.variables[1]->next->next = NULL;
    G.variables[2] = (variable*)malloc(sizeof(variable));
    G.variables[2]->no_of_tokens = 2;
    G.variables[2]->rule_no = 5;
    G.variables[2]->tokens[0] = (token*)malloc(sizeof(token));
    G.variables[2]->tokens[0]->name = 1;
    G.variables[2]->tokens[0]->is_terminal = 0;
    G.variables[2]->tokens[1] = (token*)malloc(sizeof(token));
    G.variables[2]->tokens[1]->name = 1;
    G.variables[2]->tokens[1]->is_terminal = 0;
    G.variables[2]->next = NULL;
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