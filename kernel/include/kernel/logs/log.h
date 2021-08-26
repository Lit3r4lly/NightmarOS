/**
* @file logs.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <arch/i386/ports/ports.h>

// two macros defined for stringize some macros like __LINE__
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

namespace Log {
    constexpr u16int kHackPort = 0xE9; // special "hack port" used in qemu and bochs for debugging and logging

    void Write(const char* data); // writes string to log output (stdout / file)
};

#define INIT "Initialization"
#define SUCCESS "Success"
#define ERROR "Error"
#define PANIC "Panic"

#ifdef _K_LOG // if defined - log will be created
    #define K_LOG(status, data) \
        Log::Write("[" status " - "); \
        Log::Write(__FILE__ "::"); \
        Log::Write(STRINGIZE(__LINE__) "::"); \
        Log::Write(__FUNCTION__); \
        Log::Write("] - " data);\
        Log::Write("\n");
#else // if not defined - log will not be created
    #define K_LOG(status, data)
#endif