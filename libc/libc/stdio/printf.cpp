/**
* @file printf.cpp
* @author Oshri Taub
* @brief define libc printf function
* @date 26/08/2021
* @copyright Copyright (c) 2021
*/

#include <libc/stdio.h>
#include <stdarg.h>

using out_function_type = u8int(*)(u8int);

u32int fmt_digits(int val, out_function_type out_fun);
u32int print_fmt(const char* fmt, va_list args, out_function_type out_fun);
u32int fmt_string(const char* ch, out_function_type out_fun);

/**
 * printing and formatting string using putchar
 * @param format - the format to print the string
 * @param ... - variadic function arguments
 * @return - how many chars have been printed
 * */
u32int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    u32int char_count = print_fmt(format, args, putchar);

    va_end(args);
    return char_count;
}

/**
 * function to handle the formatting of arguments into the string
 * @param format - the string to format the data into
 * @param args - the arguments to format
 * @param out_fun - the handler for the out method
 * */
u32int print_fmt(const char* format, va_list args, out_function_type out_fun) {
    u32int char_count = 0;
    for (;*format != '\0';format++) {
        if (*format != '%'){
            char val = *format;
            out_fun((int)val);
            char_count++;
        } else {
            switch (*(++format)) {
                case 'd': {
                    int val = va_arg(args, int);
                    if (val < 0){
                        out_fun((int)'-');
                        val *= -1;
                    }

                    char_count += fmt_digits(val, out_fun);
                    break;
                } case 'c': {
                    out_fun(va_arg(args, int));
                    char_count++;
                    break;
                } case 's': {
                    char_count += fmt_string(va_arg(args, const char*), out_fun);
                    break;
                }
            }
        }
    }
    return char_count;
}

/**
 * function to format a string
 * @param ch - the string to print its char
 * @param out_fun - the handler for the out method
 * @return - how many chars have been printed
 * */
u32int fmt_string(const char* ch, out_function_type out_fun){
    u32int counter = 0;
    for (;*ch != '\0';ch++) {
        out_fun((int)*ch);
        counter++;
    }
    return counter;
}


/**
 * function to format number digits
 * @param val - the number to print its digits
 * @param out_fun - the handler for the out method
 * @return - how many chars have been printed
 * */
u32int fmt_digits(int val, out_function_type out_fun) {
    if (val / 10 == 0) {
        out_fun(val + 48);
        return 1;
    } else {
        int count = fmt_digits(val / 10, out_fun);
        out_fun((val % 10) + 48);
        return count + 1;
    }
}