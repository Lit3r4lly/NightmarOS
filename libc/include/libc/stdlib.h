//
// Created by ori on 8/19/21.
//

#pragma once

#include <libc/ldefines.h>

#ifdef __cplusplus
C_SCOPE {
#endif
    NO_RETURN void abort(); // abort the run and gets into infinite loop
    int atoi(const char* str); // convert char array to int
#ifdef __cplusplus
};
#endif