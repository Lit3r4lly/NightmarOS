/**
* @file fmt.cpp
* @author Oshri Taub
* @brief define libc wrappers
* @date 01/09/2021
* @copyright Copyright (c) 2021
*/

#include <wrappers/fmt/fmt.h>

/**
* function to handle the formatting of arguments into the string
* @param format - the string to format the data into
* @param args - the arguments to format
* @param out_fun - the handler for the out method
* */
uint32_t fmt(const char* format, va_list args, out_function_type out_fun) {
    uint32_t char_count = 0;

    for (;*format != '\0';format++) {
        if (*format != '%'){
            char val = *format;
            out_fun((int)val);
            char_count++;
        } else {
            switch (*(++format)) {
                case 'd': { //print the number in 10 base
                    int val = va_arg(args, int32_t);
                    if (val < 0){
                        out_fun((uint8_t)'-');
                        char_count++;
                        val *= -1;
                    }

                    char_count += fmt_digits(val, 10,out_fun);
                    break;
                } case 'c': { //print char
                    out_fun(va_arg(args, uint32_t));
                    char_count++;

                    break;
                } case 's': { //print string
                    char_count += fmt_string(va_arg(args, const char*), out_fun);

                    break;
                } case 'u': { //print unsigned number
                    char_count += fmt_digits(va_arg(args, uint32_t), 10, out_fun);

                    break;
                } case 'b': { //print the number in 2 base
                    char_count += fmt_string("0b", out_fun);
                    char_count += fmt_digits(va_arg(args, uint32_t), 2, out_fun);

                    break;
                } case 'x' : { //print the number in 16 base
                    char_count += fmt_string("0x", out_fun); //TODO (add overflow check 0xffffffff)
                    char_count += fmt_digits(va_arg(args, uint32_t), 16, out_fun);

                    break;
                } case 'o': { //print the number in 8 base
                    char_count += fmt_string("0o", out_fun);
                    char_count += fmt_digits(va_arg(args, uint32_t), 8, out_fun);

                    break;
                } case 'p': {
                    char_count += fmt_string("0x", out_fun);
                    char_count += fmt_digits(va_arg(args, uint32_t), 16, out_fun);
                    break;
                }case '%': { //print %
                    out_fun((uint8_t)'%');
                    char_count++;
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
uint32_t fmt_string(const char* ch, out_function_type out_fun){
    uint32_t counter = 0;

    for (;*ch != '\0';ch++) {
        out_fun((int)*ch);
        counter++;
    }

    return counter;
}


/**
 * function to format number digits
 * @param val - the number to print its digits
 * @param out_fun - the handler for the out methode
 * @param base - the base to print the number in
 * @return - how many chars have been printed
 * */
uint32_t fmt_digits(uint32_t val, uint8_t base, out_function_type out_fun) {
    const char kAlphabet[kMaxBase + 1] = "0123456789ABCDEF";
    char conv_buffer[kBufSize];
    uint8_t curr_pos = kBufSize - 1;
    uint32_t char_counter = 0;

    do {
        conv_buffer[curr_pos--] = kAlphabet[val % base];
        val /= base;
        char_counter++;
    } while(val);
    curr_pos++;

    while(curr_pos < kBufSize) {
        out_fun(conv_buffer[curr_pos++]);
    }

    return char_counter;
}