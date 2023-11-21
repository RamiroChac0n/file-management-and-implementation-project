
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

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

#define DB_HOST "127.0.0.1"
#define DB_PORT 33060
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "banking_system"

#define ACCOUNT_QUERY "SELECT * FROM account WHERE id_account = ?"
#define BANK_QUERY "SELECT * FROM bank WHERE id_bank = ?"
#define TYPE_QUERY "SELECT * FROM type WHERE id_type = ?"
#define OWNER_QUERY "SELECT * FROM client WHERE id_client = ?"

#define OWNER_INSERT "INSERT INTO client (id_client, name, email, phone_number) VALUES (?, ?, ?, ?)"
#define ACCOUNT_INSERT "INSERT INTO account (id_account, password, balance, id_bank, id_type, id_client) VALUES (?, ?, ?, ?, ?, ?)"

MYSQL *connect_to_database() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

int test_database_connection() {
    MYSQL *conn = connect_to_database();
    if (conn == NULL) {
        return 0;
    } else {
        return 1;
    }
}

Bank *get_bank(int id_bank){
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[1];
    MYSQL_BIND result[4];
    Bank *bank = malloc(sizeof(Bank));
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, BANK_QUERY, strlen(BANK_QUERY)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_bank;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &bank->id_bank;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = bank->name = malloc(255);
    result[1].buffer_length = 255;
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = bank->address = malloc(255);
    result[2].buffer_length = 255;
    result[3].buffer_type = MYSQL_TYPE_LONG;
    result[3].buffer = &bank->employees;
    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_bind_result(stmt, result) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_fetch(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return bank;
}

Type *get_type(int id_type){
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[1];
    MYSQL_BIND result[2];
    Type *type = malloc(sizeof(Type));
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, TYPE_QUERY, strlen(TYPE_QUERY)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_type;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &type->id_type;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = type->name = malloc(255);
    result[1].buffer_length = 255;
    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_bind_result(stmt, result) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_fetch(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return type;
}

Owner *get_owner(int id_owner){
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[1];
    MYSQL_BIND result[4];
    Owner *owner = malloc(sizeof(Owner));
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, OWNER_QUERY, strlen(OWNER_QUERY)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_owner;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &owner->id_owner;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = owner->name = malloc(255);
    result[1].buffer_length = 255;
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = owner->email = malloc(255);
    result[2].buffer_length = 255;
    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = owner->phone_number = malloc(255);
    result[3].buffer_length = 255;
    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_bind_result(stmt, result) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_fetch(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return owner;
}

Account *get_account(int id_account) {
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[1];
    MYSQL_BIND result[6];

    int id_bank;
    int id_type;
    int id_owner;

    Account *account = malloc(sizeof(Account));
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, ACCOUNT_QUERY, strlen(ACCOUNT_QUERY)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_account;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &account->id_account;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = account->password = malloc(255);
    result[1].buffer_length = 255;
    result[2].buffer_type = MYSQL_TYPE_DOUBLE;
    result[2].buffer = &account->balance;
    result[3].buffer_type = MYSQL_TYPE_LONG;
    result[3].buffer = &id_bank;
    result[4].buffer_type = MYSQL_TYPE_LONG;
    result[4].buffer = &id_type;
    result[5].buffer_type = MYSQL_TYPE_LONG;
    result[5].buffer = &id_owner;
    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_bind_result(stmt, result) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_fetch(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }

    Bank *bank = get_bank(id_bank);
    Type *type = get_type(id_type);
    Owner *owner = get_owner(id_owner);

    account->bank = bank;
    account->type = type;
    account->owner = owner;

    mysql_stmt_close(stmt);
    mysql_close(conn);
    return account;
}

int create_owner(int id_owner, char *name, char *email, char *phone_number) {
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[4];
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, OWNER_INSERT, strlen(OWNER_INSERT)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }

    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_owner;
    param[1].buffer_type = MYSQL_TYPE_STRING;
    param[1].buffer = name;
    param[1].buffer_length = strlen(name);
    param[2].buffer_type = MYSQL_TYPE_STRING;
    param[2].buffer = email;
    param[2].buffer_length = strlen(email);
    param[3].buffer_type = MYSQL_TYPE_STRING;
    param[3].buffer = phone_number;
    param[3].buffer_length = strlen(phone_number);

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
    return 1;
}

int create_account(int id_account, char *password, double balance, int id_bank, int id_type, int id_owner) {
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[6];
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, ACCOUNT_INSERT, strlen(ACCOUNT_INSERT)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }

    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = &id_account;
    param[1].buffer_type = MYSQL_TYPE_STRING;
    param[1].buffer = password;
    param[1].buffer_length = strlen(password);
    param[2].buffer_type = MYSQL_TYPE_DOUBLE;
    param[2].buffer = &balance;
    param[3].buffer_type = MYSQL_TYPE_LONG;
    param[3].buffer = &id_bank;
    param[4].buffer_type = MYSQL_TYPE_LONG;
    param[4].buffer = &id_type;
    param[5].buffer_type = MYSQL_TYPE_LONG;
    param[5].buffer = &id_owner;

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
    return 1;
}

int set_balance(int id_account, double balance) {
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[2];
    if (stmt == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    char *query = "UPDATE account SET balance = ? WHERE id_account = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(1);
    }

    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_DOUBLE;
    param[0].buffer = &balance;
    param[1].buffer_type = MYSQL_TYPE_LONG;
    param[1].buffer = &id_account;

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
    return 1;
}