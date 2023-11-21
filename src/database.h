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
int create_owner(int id_owner, char *name, char *email, char *phone_number);
int create_account(int id_account, char *password, double balance, int id_bank, int id_type, int id_owner);

int set_balance(int id_account, double balance);

int delete_account(int id_owner);

#endif // DATABASES_H