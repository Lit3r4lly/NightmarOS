/**
* @file fmt.h
* @author Oshri Taub
* @brief declare libc wrappers
* @date 01/09/2021
* @copyright Copyright (c) 2021
*/
#pragma once

#include <libc/ldefines.h>

using out_function_type = uint8_t(*)(uint8_t);
constexpr uint8_t kMaxBase = 16;
constexpr uint8_t kBufSize = 64;

#ifdef __cplusplus
C_SCOPE {
#endif

    uint32_t fmt_digits(uint32_t val, uint8_t base, out_function_type out_fun); //function to format number digits
    uint32_t fmt(const char* fmt, va_list args, out_function_type out_fun); //function to handle the formatting of arguments into the string
    uint32_t fmt_string(const char* ch, out_function_type out_fun); //function to format a string

#ifdef __cplusplus
};
#endif