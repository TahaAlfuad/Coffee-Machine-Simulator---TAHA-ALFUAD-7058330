#include <stdio.h>

#define TOBEPROCESSED 10

int main() {
    int balance = 1000;
    
   
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};

    int num_transaction = sizeof(transactions)/sizeof(transactions[0]);

    int tobeprocessed[TOBEPROCESSED];


    for (int i=0; i < num_transaction; i++){
        int transaction = transactions[i];
     if (transaction < 0){
        if(balance + transaction < 0)
        printf("invalid transaction, Withdrawal exceeds current balance\n");
        
        tobeprocessed[i]= transaction;

        continue;
     }

     balance=+transaction;

     if(balance==0){
        printf("no further transactions will be processed");
        break; 
     }
    }

    










