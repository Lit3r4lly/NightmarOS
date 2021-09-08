/**
* @file logs.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>
#include <kernel/ports/ports.h>
#include <wrappers/fmt/fmt.h>

// two macros defined for stringize some macros like __LINE__
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

namespace Log {
    constexpr u16int kHackPort = 0xE9; // special "hack port" used in qemu and bochs for debugging and logging

    u8int WriteChar(u8int ch); // writes char to log output (stdout / file)
    void Write(const char* format, ...); // writes string to log output (stdout / file)
};

#define VA_ARGS(...) , ##__VA_ARGS__

#ifdef _K_LOG // if defined - log will be created
    #define K_LOG(fmt, ...) \
        Log::Write("["); \
        Log::Write(__FILE__ "::"); \
        Log::Write(STRINGIZE(__LINE__) "::"); \
        Log::Write(__FUNCTION__); \
        Log::Write("] - "); \
        Log::Write(fmt VA_ARGS(__VA_ARGS__)); \
        Log::Write("\n");
#else // if not defined - log will not be created
    #define K_LOG(status, data)
#endif