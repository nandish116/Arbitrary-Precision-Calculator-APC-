#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node                     //Structure Node for List
{
    struct Node * prev;
    int data;
    struct Node * next;
}Dlist;

typedef enum{                           //return values
    success,
    failure
}Status;



#define RED     "\033[31m"              //Macros for colors for printing
#define GREEN   "\033[32m"
#define YLW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RST   "\033[0m"
#define BOLD    "\033[1m"
#define DASH "--------------------------------------------\n"
// Function Declarations
Status valid(Dlist ** head1,Dlist ** tail1,Dlist ** head2,Dlist ** tail2,int argc,char * argv[]);
Status insert_last(Dlist ** head,Dlist ** tail,int data);
Status operation_type(int op,int flag,Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t,char);
Status addition(Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t);
Status subtraction(Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t);
Status multiply(Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t);
Status division(Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t);
Status insert_first(Dlist ** head,Dlist ** tail,int data);
Status copy_list(Dlist * s_head, Dlist * s_tail,Dlist ** d_head,Dlist ** d_tail);
Status delete_list(Dlist ** head,Dlist **tail);
int compare_lists(Dlist * tail1,Dlist * tail2);
void print(Dlist * head);

#endif