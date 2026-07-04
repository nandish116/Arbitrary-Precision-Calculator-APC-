#include "header.h"

void print(Dlist * head){                               //for printing list
    if(!head){                                          //If list is empty
        printf(YLW"INFO : List is empty\n"RST);
        return;
    }
    
    for(;head != NULL; head = head->next){
        printf("%d",head->data);
    }
    printf("\n");
}