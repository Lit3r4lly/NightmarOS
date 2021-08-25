/**
* @file strlen.cpp
* @author Ori Feldman
* @brief define strlen libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/string.h>

/**
 * calculates string (null terminated) length
 * @param str - desired string
 * @return string length
 */
size_t strlen(const char* str) {
    size_t str_len = 0;
    while (str[str_len])
        str_len++;

    return str_len;
}
