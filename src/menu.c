
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "utility.h"

void login() {
    system("clear");
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
        printf("Balance: $%.2f\n", account->balance);
        printf("Bank: %d\n", account->id_bank);
        printf("Type: %d\n", account->id_type);
        printf("Client: %d\n", account->id_client);

        getchar();  
    } else {
        printf("Login Failed\n");
    }
}

void transfer_money() {
    system("clear");
    printf("Transfer Money function\n");
    getchar();
}

void principal_menu() {
  int option;
  do {
    system("clear");
    printf("Select an option:\n");
    printf("1. Login\n");
    printf("2. Transfer Money\n");
    printf("0. Exit\n");
    scanf("%d", &option);
    switch (option) {
      case 1:
        login();
        break;
      case 2:
        transfer_money();
        break;
      case 0:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid option\n");
        break;
    }
  } while (option != 0);
}
