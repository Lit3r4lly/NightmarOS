/**
* @file memset.cpp
* @author Ori Feldman
* @brief define memset libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/string.h>

/**
 * copies to the first n cells the c char
 * @param dest - destination string
 * @param c - desired character
 * @param n - number of copies
 * @return the copied buffer
 */
void* memset(void* dest, int c, size_t n) {
    unsigned char* buffer = (unsigned char*)dest;
    for (size_t i = 0; i < n; ++i)
        buffer[i] = (unsigned char)c;

    return buffer;
}