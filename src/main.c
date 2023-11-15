#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void login();
void remove_newline(char *str);

int main(int argc, char *argv[]) {
    test_database_connection();
    login();
    return 0;
}

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}


void login() {
    int id_account;
    char *password = malloc(100);
    printf("Login\n");
    printf("Account Number: ");
    fflush(stdin);
    scanf("%d", &id_account);

    while (getchar() != '\n');
    printf("Password: ");
    fgets(password, 100, stdin);

    remove_newline(password);

    Account *account = get_account(id_account);

    if(account != NULL && strcmp(account->password, password) == 0) {
        system("clear");
        printf("Login Successful\n\n");
        printf("Account Number: %d\n", account->id_account);
        printf("Password: %s\n", account->password);
        printf("Funds: $%.2f\n", account->funds);
        printf("Bank: %d\n", account->id_bank);
        printf("Type: %d\n", account->id_type);
        printf("Client: %d\n", account->id_client);        
    } else {
        printf("Login Failed\n");
    }
}