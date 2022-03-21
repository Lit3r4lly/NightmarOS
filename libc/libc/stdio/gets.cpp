/**
* @file gets.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 21/03/2022
* @copyright Copyright (c) 2022
*/

#include <libc/stdio.h>
#include <kernel/keyboard/keyboard.h>

void gets(char* p) {
    Keyboard::read(p);
}