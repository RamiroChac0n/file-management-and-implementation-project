
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "utility.h"

void transfer_money() {
    system("clear");
    printf("Transfer Money function\n");

    clear_buffer();
    getchar();
}

void account_statement(Account *account) {
    system("clear");
    printf("Account Number: %d\n", account->id_account);
    printf("Password: %s\n", account->password);
    printf("Balance: %f\n", account->balance);
    printf("Bank: %d\n", account->id_bank);
    printf("Type: %d\n", account->id_type);
    printf("Owner: %d\n", account->id_client);
    
    clear_buffer();
    getchar();
}

void login() {
    system("clear");
    int id_account;
    char *password = malloc(100);
    printf("Login\n");
    printf("Account Number: ");
    fflush(stdin);
    scanf("%d", &id_account);

    clear_buffer();
    printf("Password: ");
    fgets(password, 100, stdin);

    remove_newline(password);

    Account *account = get_account(id_account);

    if(account != NULL && strcmp(account->password, password) == 0) {
        system("clear");
        printf("Login Successful");
        getchar();

        int option;
        do{
            system("clear");
            printf("Select an option:\n");
            printf("1. Account Statement\n");
            printf("2. Tranfer Money\n");
            printf("0. Log out\n");
            scanf("%d", &option);
            switch(option){
                case 1:
                    account_statement(account);
                    break;
                case 2:
                    transfer_money();
                    break;
                case 0:
                    system("clear");
                    printf("Logging out...");
                    break;
                default:
                    system("clear");
                    printf("Invalid option!!!");
                    clear_buffer();
                    getchar();
                    break;
            }
        }while(option != 0);
        clear_buffer();
        getchar();  
    } else {
        system("clear");
        printf("Login Failed!!!");
        getchar();
    }
}

void deposit_money() {
    system("clear");
    printf("Deposit Money function\n");
    clear_buffer();
    getchar();
}

void principal_menu() {
  int option;
  do {
    system("clear");
    printf("Select an option:\n");
    printf("1. Login\n");
    printf("2. Deposit Money\n");
    printf("0. Exit\n");
    scanf("%d", &option);
    switch (option) {
      case 1:
        login();
        break;
      case 2:
        deposit_money();
        break;
      case 0:
        printf("Exiting...\n");
        break;
      default:
        system("clear");
        printf("Invalid option!!!");
        clear_buffer();
        getchar();
        break;
    }
  } while (option != 0);
}
