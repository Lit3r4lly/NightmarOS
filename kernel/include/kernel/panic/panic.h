/**
* @file panic.h
* @author Ori Feldman
* @brief declare kernel panic
* @date 9/2/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>
#include <libc/stdio.h>

namespace Panic {
    // panic and get into infinite loop
    NO_RETURN void volatile Panic(const char* info, const char* file_name, const char* function_name, const uint32_t line);
};