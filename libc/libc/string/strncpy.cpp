//
// Created by ori on 8/23/21.
//

#include <libc/string.h>

/**
 *
 * @param dest
 * @param src
 * @param n
 * @return
 */
char* strncpy(char* dest, const char* src, size_t n) {
    char* ptr = dest;

    if (::strlen(src) > ::strlen(dest))
        return (char*)EOF; // TODO: add kernel panic

    for (size_t i = 0; i < n && src[i]; ++i)
        dest[i] = src[i];
    
    *dest = '\0';
    return ptr;
}