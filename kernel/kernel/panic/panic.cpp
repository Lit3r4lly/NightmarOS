/**
* @file panic.cpp
* @author Ori Feldman
* @brief define kernel panic
* @date 9/2/21
* @copyright Copyright (c) 2021
*/

#include <kernel/panic/panic.h>

/**
 * panic and get into infinite loop
 * @param info - short brief of the problem
 * @param file_name - file name where the panic occurs
 * @param function_name - function name where the panic occurs
 * @param line - line number where the panic occurs
 */
NO_RETURN void volatile Panic::Panic(const char* info, const char* file_name, const char* function_name, const u32int line) {
    printf("----- Kernel Panic -----\n");
    printf("[^] File name: %s\n", file_name);
    printf("[^] Line number: %d\n", line);
    printf("[^] Function name: %s\n", function_name);
    printf("[*] Information: %s\n", info);

    asm volatile ("cli;"); // disable interrupts
    while(true)
        asm volatile ("hlt;"); // get into infinite loop and halts the cpu
}