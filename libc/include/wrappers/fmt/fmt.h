/**
* @file fmt.h
* @author Oshri Taub
* @brief declare libc wrappers
* @date 01/09/2021
* @copyright Copyright (c) 2021
*/
#pragma once

#include <libc/ldefines.h>

using out_function_type = u8int(*)(u8int);
constexpr u8int kMaxBase = 16;
constexpr u8int kBufSize = 64;

#ifdef __cplusplus
C_SCOPE {
#endif

    u32int fmt_digits(int val, u8int base,out_function_type out_fun); //function to format number digits
    u32int fmt(const char* fmt, va_list args, out_function_type out_fun); //function to handle the formatting of arguments into the string
    u32int fmt_string(const char* ch, out_function_type out_fun); //function to format a string

#ifdef __cplusplus
};
#endif