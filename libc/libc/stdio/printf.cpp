/**
* @file printf.cpp
* @author Oshri Taub
* @brief define libc printf function
* @date 26/08/2021
* @copyright Copyright (c) 2021
*/

#include <libc/stdio.h>
#include <stdarg.h>

int print_digits(int val);

/**
 * printing and formatting string using putchar
 * @param format - the format to print the string
 * @param ... - variadic function arguments
 * @return - how many chars have been printed
 * */
int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int char_count = 0;

    for (;*format != '\0';format++) {
        if (*format != '%'){
            char val = *format;
            putchar((int)val);
            char_count++;
        } else {
            switch (*(++format)) {
                case 'd': {
                    int val = va_arg(args, int);
                    if (val < 0){
                        putchar((int)'-');
                        val *= -1;
                    }

                    char_count += print_digits(val);
                    break;
                } case 'c': {
                    putchar(va_arg(args, int));
                    char_count++;
                    break;
                } case 's': {
                    for (const char* val = va_arg(args, const char*); *val != '\0'; val++){
                        putchar((int)*val);
                        char_count++;
                    }
                    break;
                }
            }
        }
    }

    va_end(args);
    return char_count;
}

/**
 * function to print the given number digits
 * @param val - the number to print its digits
 * @return - how many chars have been printed
 * */
int print_digits(int val) {
    if (val / 10 == 0) {
        putchar(val + 48);
        return 1;
    }
    else{
        int count = print_digits(val / 10);
        putchar((val % 10) + 48);
        return count + 1;
    }
}