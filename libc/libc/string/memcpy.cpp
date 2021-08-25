/**
* @file memcpy.cpp
* @author Ori Feldman
* @brief define memcpy libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/string.h>

/**
 * copy buffer to another one
 * @param dstptr - destination pointer
 * @param srcptr - source pointer
 * @param size - size of destination pointer
 * @return the copied buffer
 */
void *memcpy(void *dstptr, const void *srcptr, size_t size) {
    unsigned char* dst = (unsigned char*)dstptr;
    const unsigned char* src = (const unsigned char*)srcptr;

    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];

    return dstptr;
}