/**
* @file printf.cpp
* @author Oshri Taub
* @brief define libc printf function
* @date 26/08/2021
* @copyright Copyright (c) 2021
*/

#include <libc/stdio.h>
#include <wrappers/fmt/fmt.h>

/**
 * printing and formatting string using putchar
 * @param format - the format to print the string
 * @param ... - variadic function arguments
 * @return - how many chars have been printed
 * */
uint32_t printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    uint32_t char_count = fmt(format, args, putchar);

    va_end(args);
    return char_count;
}