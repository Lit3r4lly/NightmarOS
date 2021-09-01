/**
* @file ldefines.h
* @author Ori Feldman
* @brief libc common definitions
* @date 8/19/21
* @copyright Copyright (c) 2021
*/

#pragma once

// freestanding headers
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#define EOF (-1)

#define C_SCOPE extern "C"
#define ASM_SCOPE extern "C"

// set aliases for some types
using uchar = unsigned char;
using uint = unsigned int;
using u8int = uint8_t;
using s8int = int8_t;
using u16int = uint16_t;
using s16int = int16_t;
using s32int = int32_t;
using u32int = uint32_t;
using u64int =  uint64_t;

#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wattributes"
    #define IGNORE(warning) GCC diagnostic ignored "warning"
    #define PACKED __attribute__((packed))
    #define NO_RETURN __attribute__((__noreturn__))
#endif