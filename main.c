#include "header.h"

int main(int argc,char* argv[]){                            //Passing CLAs
    Dlist * head1 = NULL,*tail1 = NULL;                     //Declaring operands and result linked lists
    Dlist *head2 = NULL,*tail2 = NULL;
    Dlist* res_h = NULL,*res_t = NULL;
    int flag = 0,op=0;
    printf("\n"DASH"\n");
    printf("INFO : Validating Arguements.....\n");
    if(valid(&head1,&tail1,&head2,&tail2,argc,argv)){       //Validating Arguments
        printf(RED"ERROR : Not Valid Arguments\n"RST);
        return 1;
    }else{
        printf(GREEN"VALID ARGUMENTS!!\n\n"RST);
    }
    if((argv[1][0] == '-' && argv[3][0] == '-')){           //for both negative args
        op = 3;
    }else if(argv[1][0] == '-' && argv[3][0] != '-'){       //for 1st arg is negative
        op = 1;
    }else if(argv[1][0] != '-' && argv[3][0] == '-'){       //for 3rd arg is negative
        op = 2;
    }
    if((!strcmp(argv[1],"0"))){                             //if 1st arg is 0
        flag = 1;
    }
    if((!strcmp(argv[3],"0"))){                             //if 3rd arg is 0
        flag = 2;
    }
    if((!strcmp(argv[1],"1"))){                             //if 1st arg is 1
        flag = 3;
    }
    if((!strcmp(argv[3],"1"))){                             //if 3rd arg is 1
        flag = 4;
    }
    printf("INFO : Checking Operation.....\n");
    operation_type(op,flag,tail1,tail2,&res_h,&res_t,argv[2][0]);
    printf(DASH);
    printf(YLW"\tOperand 1 ==> "RST);
    print(head1);                                           //printing operands lists
    printf(YLW"\tOperand 2 ==> "RST);
    print(head2);
    printf(DASH);
    printf(GREEN"\tResult ==> "RST);
    print(res_h);
    printf(DASH);
    return 0;
}