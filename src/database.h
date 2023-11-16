#ifndef DATABASES_H
#define DATABASES_H

typedef struct{
    int id_bank;
    char *name;
    char *address;
    int employees;
} Bank;

typedef struct{
    int id_type;
    char *name;
} Type;

typedef struct{
    int id_owner;
    char *name;
    char *email;
    char *phone_number;
} Owner;

typedef struct {
    int id_account;
    char *password;
    double balance;
    Bank *bank;
    Type *type;
    Owner *owner;
} Account;

int test_database_connection();

Bank *get_bank(int id_bank);
Type *get_type(int id_type);
Owner *get_owner(int id_owner);
Account *get_account(int id_account);

#endif // DATABASES_H