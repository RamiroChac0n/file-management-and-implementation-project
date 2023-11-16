#ifndef DATABASES_H
#define DATABASES_H

typedef struct{
    int id_bank;
    char *name;
    char *address;
    int employees;
} Bank;

typedef struct {
    int id_account;
    char *password;
    double balance;
    Bank *bank;
    int id_type;
    int id_client;
} Account;

int test_database_connection();

Bank *get_bank(int id_bank);
Account *get_account(int id_account);

#endif // DATABASES_H