#ifndef IO_H
#define IO_H

#define UART_BASE 0x10000000
#define UART_LSR  (UART_BASE + 5)  // Line Status Register

void print(char* str);
char get_char();
void print_int(unsigned long long int num);
void input();
void print_char(char c);
void read_line(char* buffer, int size);

#endif