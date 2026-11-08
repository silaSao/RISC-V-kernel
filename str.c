#include <stddef.h>
#include "str.h"

int str_equal(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && (str1[i] == str2[i])) {
        i++;
    }
    return str1[i] == str2[i];
}

