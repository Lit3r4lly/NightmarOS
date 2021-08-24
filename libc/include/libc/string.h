//
// Created by ori on 8/19/21.
//

#pragma once

#include <libc/ldefines.h>

#ifdef __cplusplus
C_SCOPE {
#endif

    size_t strlen(const char* str); // calculate string length
    char* strcpy(char* dest, const char* src); // copy string to another one
    char* strncpy(char* dest, const char* src, size_t n); // copy string to another one by size
    int strcmp(const char* str1, const char* str2); // compare between 2 strings
    void* memset(void* dest, int c, size_t n); // copies character to the first n cells in the destination
    void *memcpy(void *dstptr, const void *srcptr, size_t size); // copy buffer to another buffer

#ifdef __cplusplus
};
#endif