#ifndef duduzinho_h_
#define duduzinho_h_

// Struct's declaration
struct account{
    int id;
    float balance;
};
// Redefinition of type
typedef struct account Account;

// Creation of a new account
Account createAccount(int id);
// Print the client actual profile
void printAccount(Account client);
// Credit x dollars to your account
Account addMoney(Account client);
// Debit x dollars to your account
Account debitMoney(Account client);

#endif /* duduzinho_h_ */