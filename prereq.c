#include"header.h"

Status valid(Dlist ** head1,Dlist ** tail1,Dlist ** head2,Dlist ** tail2,int argc,char * argv[]){
    char opr[] ={'+','-','*','/'};                          //all operators in array
    if(argc != 4){                                          //for validating no of args
        printf(RED"ERROR : Only 4 arguments are valid\n");
        return failure;
    }

    for(int i = 0;argv[3][i];i++){                          //for validating arg and storing in linked list
        if(argv[3][i] == '-'){
            i = 1;
        }
        if((argv[3][i] - 48 <= 9) && (argv[3][i] - 48 >= 0)){
            int data = argv[3][i] - 48;
            insert_last(head2,tail2,data);
        }else{
            printf(RED"ERROR : Enter only numbers as operands\n"RST);
            return failure;
        }
    }
    
    for(int i = 0;argv[1][i];i++){                           //for validating arg and storing in linked list
        if(argv[1][i] == '-'){
            i = 1;
        }
        if((argv[1][i] - 48 <= 9) && (argv[1][i] - 48 >= 0)){
            int data = argv[1][i] - 48;
            insert_last(head1,tail1,data);
        }else{
            printf(RED"ERROR : Enter only numbers as operands\n"RST);
            return failure;
        }
    }

    if(strlen(argv[2]) != 1){                                 //for validating sign
        printf(BLUE"Allowed operators are '+','-','*','/'\n"RST);
        return failure;
    }

    for(int j = 0; j < 4;j++){                                //for validating sign
        if(argv[2][0] == opr[j]){
            return success;
        }
    }
    return failure;
    
}

Status operation_type(int op,int flag,Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t,char sign){
    switch (sign){
    case '+':
        printf(BLUE"Adding two numbers......\n"RST);
        if(op == 1){                                         //if 1st arg is negative 
            if(compare_lists(tail2,tail1) > 0){              //if 2nd arg is larger
                subtraction(tail2,tail1,res_h,res_t);
            }else{
                subtraction(tail1,tail2,res_h,res_t);       //else, add negative sign
                (*res_h)->data = -1 * (*res_h)->data;
            }
        }else if(op == 2){                                  //if 2nd arg is negative 
            if(compare_lists(tail1,tail2) > 0){             //if 1nd arg is larger
                subtraction(tail1,tail2,res_h,res_t);
            }else{                                          //else, add negative sign
                subtraction(tail2,tail1,res_h,res_t);
                (*res_h)->data = -1 * (*res_h)->data;
            }
        }else if(op == 3){                                  //if both are negative
            addition(tail1,tail2,res_h,res_t);
            (*res_h)->data = -1 * (*res_h)->data;
        }else{                                              //else both are negative
            addition(tail1,tail2,res_h,res_t);
        }
        break;
    case '-':
        printf(BLUE"Subtracting two numbers.......\n"RST);
        if(compare_lists(tail1,tail2) == 0){                //if both are same
            insert_first(res_h,res_t,0);
            break;
        }
        if(op == 3){                                        
            if(compare_lists(tail1,tail2) > 0){             //if 1st arg is larger
                subtraction(tail1,tail2,res_h,res_t);
                (*res_h)->data = -1 * (*res_h)->data;
            }else{
                subtraction(tail2,tail1,res_h,res_t);       //passing larger one as first arg
            }
        }else if(op == 1){                                  //if 1st arg is negative
            if(compare_lists(tail1,tail2) > 0){
                subtraction(tail1,tail2,res_h,res_t);
            }else{
                subtraction(tail2,tail1,res_h,res_t);       //passing larger one as first arg
                (*res_h)->data = -1 * (*res_h)->data;
            }
        }else if(op == 2){
            addition(tail1,tail2,res_h,res_t);
        }else{
            if(compare_lists(tail1,tail2) > 0){             //if 3rd arg is negative
                subtraction(tail1,tail2,res_h,res_t);
            }else{
                subtraction(tail2,tail1,res_h,res_t);
                (*res_h)->data = -1 * (*res_h)->data;
            }
        }
        break;
     case '*':
        printf(BLUE"Multiplying two numbers....\n"RST);
        if(flag == 1 || flag == 2){                         //if one of the args is 0
            insert_first(res_h,res_t,0);
        }else if(flag == 4){                                //if 3rd arg is 1,
            copy_list(NULL,tail1,res_h,res_t);              //copying other as result
        }else if(flag == 3){                                //if 1st arg is 1,
            copy_list(NULL,tail2,res_h,res_t);              //copying other as result
        }else if(compare_lists(tail1,tail2) < 0){
            multiply(tail2,tail1,res_h,res_t);
        }else{
            multiply(tail1,tail2,res_h,res_t);
        }
        if(op == 1 || op == 2){
            (*res_h)->data = -1 * (*res_h)->data;
        }
        break;
    case '/':
        printf(BLUE"Dividing two numbers....\n"RST);
        if(compare_lists(tail1,tail2) < 0){                 //if 1st arg is less than 3rd
            insert_first(res_h,res_t,0);
        }else if(compare_lists(tail1,tail2) == 0){          // if both are equal
            insert_first(res_h,res_t,1);
        }else if(flag == 4){                                //if one of the arg is 1
            copy_list(NULL,tail1,res_h,res_t);
        }else if(flag == 2){                                //if 3rd arg is 0
            printf(RED"ERROR : 0 can't be divisor\n"RST);
            return failure;
        }else{
            division(tail1,tail2,res_h,res_t);
        }
        if(op == 1 || op == 2){                             //if one arg is one
            (*res_h)->data = -1 * (*res_h)->data;
        }
        
        break;
    }
    printf(BOLD GREEN"EXECUTED SUCCESSFULLY\n\n" RST);
    return success;
}

Status insert_last(Dlist ** head,Dlist ** tail,int data){   //for inserting last
    Dlist * new = (Dlist*)malloc(sizeof(Dlist));
    if(!new){
        return failure;
    }
    new->prev = NULL;
    new->data = data;
    new->next = NULL;
    if(*head == NULL){                                      //for first node
        *head=*tail=new;
        return success;
    }
    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return success;
}

Status insert_first(Dlist ** head,Dlist ** tail,int data){  //for inserting first
    Dlist * new = (Dlist*)malloc(sizeof(Dlist));
    if(!new){
        return failure;
    }
    new->prev = NULL;
    new->data = data;
    new->next = NULL;
    if(*head == NULL){                                      //for first node
        *head = *tail = new;
        return success;
    }
    new->next = *head;
    (*head)->prev = new;
    *head = new;
    return success;
}

Status copy_list(Dlist * s_head, Dlist * s_tail,Dlist ** d_head,Dlist ** d_tail){
    if(s_head){                                             //if head is not NULL
        for(;s_head != NULL;s_head = s_head->next){
            insert_last(d_head,d_tail,s_head->data);
        }
    }
    else{                                                  //if head is null
        for(;s_tail != NULL;s_tail = s_tail->prev){
            insert_first(d_head,d_tail,s_tail->data);
        }
    }
    return success;
}

Status delete_list(Dlist ** head,Dlist **tail){             //for deleting list
    Dlist * htemp = (*head)->next,*ttemp = *tail;
    for(;htemp != NULL;htemp = htemp->next){
        free(htemp);
    }
    *head = NULL; 
    *tail = NULL;
    free(*head);
    if(*tail){
        free(*tail);
    }
    return success;
}

int compare_lists(Dlist *tail1, Dlist *tail2){              //for comparing lists
    int len1 = 0, len2 = 0;
    Dlist *temp1, *temp2, *head1, *head2;
    if(!tail1 && !tail2){                                   //if both are null
        return 0;
    }
    for (temp1 = tail1; temp1 != NULL; temp1 = temp1->prev){//for length of list 1
        len1++;
    }
    for (temp2 = tail2; temp2 != NULL; temp2 = temp2->prev){//for length of list 2
        len2++;
    }
    if (len1 > len2){
        return 1;
    }
    if (len1 < len2){
        return -1;
    }

    for (head1 = tail1; head1->prev != NULL;) head1 = head1->prev;//for taking head
    for (head2 = tail2; head2->prev != NULL;) head2 = head2->prev;
    for (temp1 = head1, temp2 = head2;temp1 != NULL && temp2 != NULL;temp1 = temp1->next, temp2 = temp2->next){
        if (temp1->data > temp2->data){                           //for comparing digit by digit from head
            return 1;
        }
        if (temp1->data < temp2->data){ 
            return -1;
        }
    }
    return 0;
}