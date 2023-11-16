
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
    printf("Bank: %s\n", account->bank->name);
    printf("Type: %s\n", account->type->name);
    printf("Owner: %s\n", account->owner->name);
    
    clear_buffer();
    getchar();
}

void login() {
    system("clear");
    int id_account;
    char *password = malloc(255);
    printf("Login\n");
    printf("Account Number: ");
    fflush(stdin);
    scanf("%d", &id_account);

    clear_buffer();
    printf("Password: ");
    fgets(password, 255, stdin);

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

char *create_password(){
    char *password = malloc(255);
    char *password_confirmation = malloc(255);
    do{
      system("clear");
      printf("Create a password: ");
      fgets(password, 255, stdin);
      printf("Confirm your password: ");
      fgets(password_confirmation, 255, stdin);

      if(strcmp(password, password_confirmation) != 0){
        system("clear");
        printf("Passwords do not match!!!");
        getchar();
      }
    }while(strcmp(password, password_confirmation) != 0);
    return password;
}

Account *request_account_information(){
    system("clear");
    int id_account = generate_account_number();
    char *password = malloc(255);
    double balance = 0;
    int id_bank = 0;
    int id_type = 0;

    int id_owner = 0;
    char *name = malloc(50);
    char *email = malloc(50);
    char *phone_number = malloc(20);

    Account *account = get_account(id_account);

    while(account != NULL){
        id_account = generate_account_number();
        account = get_account(id_account);
    }

    printf("Your account number is: %d\n", id_account);
    printf("Please, remember it!!!\n");
    printf("Press enter to continue...");
    clear_buffer();
    getchar();

    password = create_password();

    system("clear");
    printf("Enter your ID: ");
    scanf("%d", &id_bank);
    clear_buffer();
    printf("Enter your name: ");
    fgets(name, 50, stdin);
    printf("Enter your email: ");
    fgets(email, 50, stdin);
    printf("Enter your phone number: ");
    fgets(phone_number, 20, stdin);

    printf("Please, press enter to continue...");
    getchar();
    system("clear");
    printf("Account successfully created...");
    getchar();
}

void principal_menu() {
  int option;
  do {
    system("clear");
    printf("Select an option:\n");
    printf("1. Login\n");
    printf("2. Deposit Money\n");
    printf("3. Create Account\n");
    printf("0. Exit\n");
    scanf("%d", &option);
    switch (option) {
      case 1:
        login();
        break;
      case 2:
        deposit_money();
        break;
      case 3:
        request_account_information();
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
