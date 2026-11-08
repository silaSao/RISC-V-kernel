#ifndef IO_H
#define IO_H

#include <stdint.h>

#define UART_BASE 0x10000000
#define UART_LSR  (UART_BASE + 5)  

void print(char* str);
uint8_t get_char();
void print_int(unsigned long long int num);
void input();
void print_char(char c);
void read_line(char* buffer, int size);

#endif