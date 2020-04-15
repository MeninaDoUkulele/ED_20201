#include <stdio.h>
#include "duduzinho.h"

Account createAccount(int id){
    Account client;
    client.id = id;
    client.balance = 0;

    printf("Made.\n");
    return client;
}

Account addMoney(Account client){
    float value;
    Account aux;
    printf("Please press the value: ");
    scanf("%f", &value);

    aux.id = client.id;
    aux.balance = client.balance + value;
    printf("Made.\n");

    return aux;
}

Account debitMoney(Account client){
    float value;
    Account aux;
    printf("Please press the value: ");
    scanf("%f", &value);

    aux.id = client.id;
    aux.balance = client.balance - value;
    printf("Made.\n");

    return aux;
}

void printAccount(Account client){
    printf("  Owner: [ %i ]\n  Balance: [ $%.2f ]\n", client.id, client.balance);
}

