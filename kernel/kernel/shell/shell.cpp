/**
* @file shell.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 3/23/22
* @copyright Copyright (c) 2022
*/

#include <kernel/shell/shell.h>

void Shell::Initialize() {
    char current_str[1024] = { 0 };

    while (true) {
        printf(">> ");
        uint32_t size = gets(current_str);
        current_str[size - 1] = '\0';

        printf("%s\n", current_str);
    }
}