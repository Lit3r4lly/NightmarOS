/**
* @file abort.cpp
* @author Ori Feldman
* @brief define abort libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/stdlib.h>

/**
 * abort the run and gets inside infinite loop
 */
__attribute__((__noreturn__)) void abort() {
#if defined(__is_libk)
    // TODO: Add proper kernel panic and printing
    printf("[!!] kernel panic");
#else
    // TODO: Abnormally terminate the process
#endif
    while (1) { }
    __builtin_unreachable();
}