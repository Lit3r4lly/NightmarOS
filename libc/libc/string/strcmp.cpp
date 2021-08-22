//
// Created by ori on 8/23/21.
//

#include <libc/string.h>

/**
 * compare between 2 strings
 * @param str1 - first string
 * @param str2 - second string
 * @return indicator for equalization
 */
int strcmp(const char* str1, const char* str2) {
    while (*str1) {
        if (*str1 != *str2)
            break;

        str1++;
        str2++;
    }

    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}