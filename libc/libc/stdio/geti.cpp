/**
* @file geti.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 21/03/2022
* @copyright Copyright (c) 2022
*/

#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <kernel/keyboard/keyboard.h>

void geti(int32_t* p) {
    Keyboard::read(p);
    *p = atoi((char*)p);
}
