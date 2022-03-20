/**
* @file stdlib.h
* @author Ori Feldman
* @brief declare stdlib libc functions
* @date 8/19/21
* @copyright Copyright (c) 2021
*/

#pragma once


#include <libc/ldefines.h>
#include <libc/stdio.h>

#ifdef __cplusplus
C_SCOPE {
#endif
    NO_RETURN void abort(); // abort the run and gets into infinite loop
    int atoi(const char* str); // convert char array to int
    void* malloc(size_t size); //malloc aight
    void* calloc(size_t size, char ch); //same as malloc but with a char
    void free(void* p); //free the malloc space
#ifdef __cplusplus
};
#endif