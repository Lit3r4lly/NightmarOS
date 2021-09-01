/**
* @file putchar.cpp
* @author Ori Feldman
* @brief define libc putchar function
* @date 8/23/21
* @copyright Copyright (c) 2021
*/

#include <libc/stdio.h>

/**
 * printing char into the screen using TTY
 * @param ich - desired char
 * @return the char that written to the screen as int, if there is error the function would return EOF
 */
u8int putchar(u8int ich) {
#if defined(__is_libk)
    char c = (char)ich;
    TTY::PutChar(c);
#else
    // TODO: implement user-mode stdio syscalls
#endif
    return ich;
}