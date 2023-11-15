
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    int id_account;
    char *password;
    double balance;
    int id_bank;
    int id_type;
    int id_client;
} Account;

#define DB_HOST "127.0.0.1"
#define DB_PORT 33060
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "banking_system"

#define ACCOUNT_QUERY "SELECT * FROM account WHERE id_account = ?"

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

Account *get_account(int id_account) {
    MYSQL *conn = connect_to_database();
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND param[1];
    MYSQL_BIND result[6];
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
    result[3].buffer = &account->id_bank;
    result[4].buffer_type = MYSQL_TYPE_LONG;
    result[4].buffer = &account->id_type;
    result[5].buffer_type = MYSQL_TYPE_LONG;
    result[5].buffer = &account->id_client;
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
        exit(1);
    }
    
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return account;
}
