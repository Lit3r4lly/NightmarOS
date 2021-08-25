/**
* @file atoi.cpp
* @author Ori Feldman
* @brief define atoi libc function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/stdlib.h>

/**
 * convert char array to int
 * @param str - source string
 * @return the string as int number
 */
int atoi(const char* str) {
    int res = 0;

    for (size_t i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0'; // preform calculation of string into int

    return res;
}