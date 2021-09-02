/**
* @file abort.cpp
* @author Ori Feldman
* @brief define abort libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/stdlib.h>

#if defined(__is_libk)
#include <kernel/common/kuseful.h>
#endif

/**
 * abort the run and gets inside infinite loop
 */
__attribute__((__noreturn__)) void abort() {
#if defined(__is_libk)
    K_PANIC("Kernel aborted");
#else
    // TODO: Abnormally terminate the process
#endif
    while (1) { }
    __builtin_unreachable();
}