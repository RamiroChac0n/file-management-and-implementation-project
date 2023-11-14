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
    char *account_number = malloc(100);
    char *password = malloc(100);
    printf("Login\n");
    printf("Account Number: ");
    fgets(account_number, 100, stdin);
    printf("Password: ");
    fgets(password, 100, stdin);

    remove_newline(account_number);
    remove_newline(password);
}