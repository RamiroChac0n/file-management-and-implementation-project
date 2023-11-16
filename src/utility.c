#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void clear_buffer() {
    while (getchar() != '\n');
}

int generate_account_number() {
    srand(time(NULL)); // inicializar la semilla del generador de números aleatorios
    int account_number = rand() % 900000 + 100000; // generar un número aleatorio de 6 dígitos
    return account_number;
}