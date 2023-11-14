
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_PORT 33060
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "banking_system"

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

void test_database_connection() {
    MYSQL *conn = connect_to_database();
    if (conn == NULL) {
        printf("Error al conectar a la base de datos\n");
    } else {
        printf("Conexión exitosa a la base de datos\n");
        mysql_close(conn);
    }
}
