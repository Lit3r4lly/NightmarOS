//
// Created by ori on 8/23/21.
//

#include <libc/stdio.h>

/**
 * printing char into the screen using TTY
 * @param ich - desired char
 * @return the char that written to the screen as int, if there is error the function would return EOF
 */
int putchar(int ich) {
#if defined(__is_libk)
    char c = (char)ich;
    TTY::WriteString(&c);
#else
    // TODO: implement user-mode stdio syscalls
#endif
    return ich;
}