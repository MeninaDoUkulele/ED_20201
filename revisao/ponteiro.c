#include <stdio.h>
#include "duduzinho.h"

int main(){
    Account client;
    int stop = 0, id;

    while(stop != 5){
        printf("\nWhat you wanna do?\nCreate an Account [1]\nCredit [2]\nWithdraw [3]\nVerify [4]\nExit [5]\n");
        scanf("%i", &stop);
        switch(stop){
            case 1:
                if(client.id == id){
                    printf("You already have an account.\n");
                } else{
                    printf("Press the number id, please.\n");
                    scanf("%i", &id);
                    client = createAccount(id);
                }
                break;
            case 2:
                client = addMoney(client);
                break;
            case 3:
                client = debitMoney(client);
                break;
            case 4:
                printAccount(client);
                break;
            case 5:
                printf("Made.\n");
                return 0;
                break;
            default:
                printf("This command doesn't exist.\n");
                break;
        }
    }
}