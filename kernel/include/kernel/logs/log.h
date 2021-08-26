/**
* @file logs.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <arch/i386/ports/ports.h>

#ifdef _K_LOG // if defined - log will be created
    #define K_LOG(data) \
        Log::Write(data)
#else // if not defined - log will not be created
    #define K_LOG(data)
#endif

namespace Log {
    constexpr u16int kHackPort = 0xE9; // special "hack port" used in qemu and bochs for debugging and logging

    void Write(const char* data); // writes string to log output (stdout / file)
};