//
// Created by ori on 8/23/21.
//

#include <libc/string.h>

/**
 * copies src string to dest string
 * @param dest - dest string
 * @param src - src string
 * @return copy of the copied string
 */
char* strcpy(char* dest, const char* src) {
    char* ptr = dest;

    if (::strlen(src) > ::strlen(dest))
        return (char*)EOF; // TODO: add kernel panic

    for (size_t i = 0; i < ::strlen(src); ++i)
        dest[i] = src[i];

    *dest = '\0';
    return ptr;
}