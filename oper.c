#include"header.h"

Status addition(Dlist *tail1, Dlist *tail2, Dlist **res_h, Dlist **res_t){       //For adding numbers
    int carry = 0;
    while(tail1 || tail2 || carry){                                              //Operation should continue till anyone has a valid value

        int num1 = tail1 ? tail1->data : 0;                                      //Storing data       
        int num2 = tail2 ? tail2->data : 0;
        int sum = num1 + num2 + carry;                                           //adding digit with carry

        insert_first(res_h, res_t,sum%10);                                       //storing ones digit of sum
        carry = sum / 10;                                                        //storing 10s digit into carry

        if(tail1){                                                               //for moving tails to next node(digit)
            tail1 = tail1->prev;
        }
        if(tail2){
            tail2 = tail2->prev;
        }
    }
    return success;
}

Status subtraction(Dlist *tail1, Dlist *tail2, Dlist **res_h, Dlist **res_t){   //For subtracting numbers
    int num1, num2, sub;
    int borrow = 0;

    while (tail1 || tail2){                                                     //looping till either one has valid address
        if (tail1){                                                             //Storing values
            num1 = tail1->data;
        }else{
            num1 = 0;
        }
        if(tail2){
            num2 = tail2->data;
        }else{
            num2 = 0;
        }
        num1 = num1 - borrow;                                                   //Subtracting borrow with 

        if(num1 < num2){                                                        //if num1 is lesser than num2
            num1 += 10;                                                         //so adding 10 to num1
            borrow = 1;                                                         //making borrow as one
        }else{
            borrow = 0;                                                         //else borrow is 0
        }
        sub = num1 - num2;
        insert_first(res_h, res_t, sub);                                        //storing sub in list
        if (tail1){                                                             //Moving tails
            tail1 = tail1->prev;
        }
        if (tail2){
            tail2 = tail2->prev;
        }
    }
    while (*res_h && (*res_h)->data == 0 && *res_h != *res_t){                    //Removing leading 0s
        Dlist *temp = *res_h;
        *res_h = (*res_h)->next;
        (*res_h)->prev = NULL;
        free(temp);
    }
    return success;
}

Status multiply(Dlist * tail1,Dlist * tail2,Dlist ** res_h,Dlist ** res_t){        //for multiplying two numbers
    int mul,carry =0,prod,num,n;
    Dlist * temp1 = tail1, *temp2 = tail2;                                          //for temp pointers
    Dlist *t_resh1 = NULL,*t_resh2 = NULL;
    Dlist *t_rest1 = NULL,*t_rest2 = NULL;
    for(n = 0,temp2 = tail2;temp2 != NULL;temp2 = temp2->prev,n++){                 //looping till 2nd tail reaches null
        carry = 0;
        for(int i = 0;i < n;i++){                                                   //for adding zeros in the list
            insert_last(&t_resh2,&t_rest2,0);
        }
        for(temp1 = tail1;temp1 != NULL;temp1 = temp1->prev){                       //looping till head for 1st operand
            mul = temp2->data * temp1->data + carry;                                //multiplying digits
            if(!n){
                insert_first(&t_resh1,&t_rest1,mul%10);                             //storing product into list
            }else{
                insert_first(&t_resh2,&t_rest2,mul%10);
            }
            carry = mul / 10;                                                       //for carry
        }
        if(carry){                                                                  //inserting carry 
            if(!n){
                insert_first(&t_resh1,&t_rest1,carry);
            }else{
                insert_first(&t_resh2,&t_rest2,carry);
            }
            carry = 0;
        }
        if(n){                                                                      //adding carry with res
            addition(t_rest2,t_rest1,res_h,res_t);
            if(t_resh1){
                delete_list(&t_resh1,&t_rest1);                                     //deleting lists after adding
            }
            if(t_resh2){
                delete_list(&t_resh2,&t_rest2);                                 
            }
            t_resh1 = *res_h;                                                       //copying to temp_result
            t_rest1 = *res_t;
        }  
    }
    *res_h = t_resh1;                                                               //after multiplying storing into main result
    *res_t = t_rest1;
    return success;
}
Status division(Dlist *tail1, Dlist *tail2, Dlist **res_h, Dlist **res_t){          //for dividing numbers
    Dlist *h_cnt = NULL, *t_cnt = NULL;                                             //for having count(quiotent)
    Dlist *h_one = NULL, *t_one = NULL;                                             //for having adding list
    Dlist *h_temp1 = NULL, *t_temp1 = NULL;
    Dlist*h_temp2 = NULL, *t_temp2 = NULL;

    insert_first(&h_cnt, &t_cnt, 0);                                                //count as 0
    insert_first(&h_one, &t_one, 1);                                                //adder
    copy_list(NULL, tail1, &h_temp1, &t_temp1);

    while (compare_lists(t_temp1, tail2) >= 0){                                     //comparing lists to stop dividing
        subtraction(t_temp1, tail2, &h_temp2, &t_temp2);                            //subtracting dividend with divisor
        delete_list(&h_temp1, &t_temp1);                                            //deleting existing dividend
        copy_list(NULL, t_temp2, &h_temp1, &t_temp1);                               //and storing previous res as dividend
        delete_list(&h_temp2, &t_temp2);                                            //deleting result

        addition(t_cnt, t_one, &h_temp2, &t_temp2);                                 //adding count
        delete_list(&h_cnt, &t_cnt);                                                //updating count
        copy_list(NULL, t_temp2, &h_cnt, &t_cnt);
        delete_list(&h_temp2, &t_temp2);
    }

    *res_h = h_cnt;                                                                 //storing count as result
    *res_t = t_cnt;

    delete_list(&h_temp1, &t_temp1);                                                //deleting remaining lists
    delete_list(&h_one, &t_one);

    return success;
}                   