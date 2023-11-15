#ifndef DATABASES_H
#define DATABASES_H

typedef struct {
    int id_account;
    char *password;
    double funds;
    int id_bank;
    int id_type;
    int id_client;
} Account;

int test_database_connection();
Account *get_account(int id_account);

#endif // DATABASES_H