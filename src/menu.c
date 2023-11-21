
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "utility.h"

void transfer_money(Account *account) {
    double amount;
    int id_account_destination;
    printf("Enter the account number of the destination: ");
    scanf("%d", &id_account_destination);
    printf("Enter the amount to deposit: ");
    scanf("%lf", &amount);

    Account *account_destination = get_account(id_account_destination);

    if(account_destination != NULL && (amount > 0)){
        if((account->balance - amount) >= 0){
            set_balance(account->id_account, account->balance - amount);
            set_balance(account_destination->id_account, account_destination->balance + amount);
            system("clear");
            printf("Transfer successful!!!");
        }else{
            system("clear");
            printf("Insufficient funds!!!");
        }
    }else{
        system("clear");
        printf("Transfer failed!!!");
    }

    clear_buffer();
    getchar();
}

void account_statement(Account *account) {
    system("clear");
    printf("Account Number:\t%d\n", account->id_account);
    printf("Password:\t%s\n", account->password);
    printf("Balance:\t$%.2f\n", account->balance);
    printf("Bank:\t\t%s\n", account->bank->name);
    printf("Type:\t\t%s\n", account->type->name);
    printf("Owner:\t\t%s\n", account->owner->name);
    
    clear_buffer();
    getchar();
}

int close_account(Account *account) {
    system("clear");
    printf("Are you sure you want to close your account?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    int option;
    scanf("%d", &option);
    if(option == 1){
        if(delete_account(account->id_account)){
            system("clear");
            printf("Account successfully closed!!!");
            return 0;
        }else{
            system("clear");
            printf("Account closing failed!!!");
            clear_buffer();
            getchar();
            return -1;
        }
    }else{
        system("clear");
        printf("Account closing canceled!!!");
        clear_buffer();
        getchar();
        return -1;
    }
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
            printf("3. Close Account\n");
            printf("0. Log out\n");
            scanf("%d", &option);
            switch(option){
                case 1:
                    account = get_account(id_account);
                    account_statement(account);
                    break;
                case 2:
                    transfer_money(account);
                    break;
                case 3:
                    option = close_account(account);
                    break;
                case 0:
                    system("clear");
                    printf("Logging out...");
                    free(account);
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

void deposit_money(Account *account) {
    double amount;
    printf("Enter the amount to deposit: ");
    scanf("%lf", &amount);
    if((amount > 0) && set_balance(account->id_account, account->balance + amount)){
        system("clear");
        printf("Deposit successful!!!");
    }else{
        system("clear");
        printf("Deposit failed!!!");
    }
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

      remove_newline(password);
      remove_newline(password_confirmation);

      if(strcmp(password, password_confirmation) != 0){
        system("clear");
        printf("Passwords do not match!!!");
        getchar();
      }
    }while(strcmp(password, password_confirmation) != 0);
    return password;
}

int print_bank_list(){
    system("clear");
    int index = 1;
    Bank *bank = get_bank(index);

   printf("ID. \t%-40s %-25s \t%s\n\n", "Name of Bank", "Address", "Employees");

    while (bank != NULL) {
        printf("%d. \t%-40s %-25s \t%d\n", bank->id_bank, bank->name, bank->address, bank->employees);
        index++;
        bank = get_bank(index);
    }

    printf("Please, select a bank: ");
    scanf("%d", &index);
    return index;
}

int print_type_list(){
    system("clear");
    int index = 1;
    Type *type = get_type(index);

    printf("ID. \t%s\n\n", "Type of Account");

    while (type != NULL) {
        printf("%d. \t%s\n", type->id_type, type->name);
        index++;
        type = get_type(index);
    }

    printf("Please, select a type: ");
    scanf("%d", &index);
    return index;
}

void *request_account_information(int id_bank, int id_type){
    system("clear");
    int id_account = generate_account_number();
    char *password = malloc(255);
    double balance = 0.0;

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
    scanf("%d", &id_owner);
    clear_buffer();
    printf("Enter your name: ");
    fgets(name, 50, stdin);
    printf("Enter your email: ");
    fgets(email, 50, stdin);
    printf("Enter your phone number: ");
    fgets(phone_number, 20, stdin);

    printf("Please, press enter to continue...");
    getchar();

    if(create_owner(id_owner, name, email, phone_number)){
        if(create_account(id_account, password, balance, id_bank, id_type, id_owner)){
            system("clear");
            printf("Account successfully created...");
            getchar();
        }else{
            system("clear");
            printf("Account creation failed!!!");
            getchar();
        }
    }else{
        system("clear");
        printf("Owner creation failed!!!");
        getchar();
    }
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
        int id_account;
        Account *account;
        do
        {
            system("clear");
            printf("Enter your account number: ");
            scanf("%d", &id_account);
            account = get_account(id_account);
            if(account == NULL){
                system("clear");
                printf("Account not found!!!");
                clear_buffer();
                getchar();
            }
        } while (account == NULL);
        deposit_money(account);
        free(account); //CUIDADOOOOOOOOO
        break;
      case 3:
        int id_bank = print_bank_list();
        int id_type = print_type_list();
        request_account_information(id_bank, id_type);
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
