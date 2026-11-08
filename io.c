#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "str.h"

void print(char* str) {
    volatile char* letter = (volatile char*)UART_BASE;
    volatile uint8_t* lsr = (volatile uint8_t*)UART_LSR;
    while (*str != 0){
        while (!(*lsr & (1 << 5)));
        *letter = *str;
        str++;
    }
}

void input() {
    char c;
    char buffer[100];
    int i = 0;
    print_char('>');
    while (true) {
        c = get_char();
        if (c == '\n' || c == '\r') {
            buffer[i] = '\0';
            read_line(buffer, 100);
            print_char('\n');
            break;
        }
        else {
            buffer[i] = c;
            print_char(c);
            i++;
        }
    }
}

void read_line(char* buffer, int size) {
    char command[50];
    char arg1[50];

    int i = 0;
    while (i < size) {
        if (buffer[i] == ' ' || buffer[i] == '\0') {
            break;
        }
        command[i] = buffer[i];
        i++;
    }
    command[i] = '\0';

    int j = 0;
    while (i < size) {
        i++;
        if (buffer[i] == ' ' || buffer[i] == '\0') {
            break;
        }
        arg1[j] = buffer[i];
        j++;
    }
    arg1[j] = '\0';

    print_char('\n');
    if (str_equal(command, "echo")) {
        print(arg1);
    }
}

void print_char(char c) {
    volatile char* charBase = (volatile char*)UART_BASE;
    *charBase = c;
}

uint8_t get_char() {
    volatile uint8_t* lsr = (volatile uint8_t*)UART_LSR;
    volatile uint8_t* rbr = (volatile uint8_t*)UART_BASE;

    while ((*lsr & 0x01) == 0);
    return *rbr;
}

void print_int(unsigned long long int num) {
    if (num < 0) {
        print_char('-');
        num = -num;
    }
    if (num == 0) {
        print_char('0');
        return;
    }

    char temp[30];
    int i = 0;
    while (num > 0) {
        temp[i] = '0' + (num % 10);
        i++;
        num /= 10;
    }
    while (i > 0) {
        i--;
        print_char(temp[i]);
    }
}