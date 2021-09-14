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
#ifdef __cplusplus
};
#endif