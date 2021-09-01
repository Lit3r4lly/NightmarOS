/**
* @file logs.cpp
* @author Ori Feldman
* @brief this file defines the log system for the OS; using the ports I/O mechanism
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#include <kernel/logs/logs.h>

/**
 * writes char to log output (stdout / file)
 * @param ch - char to be written
 * @return the written char
 */
u8int Log::WriteChar(u8int ch) {
    if (ch < 10 and ch > 0)
        ch += '0';

    Ports::OutB(Log::kHackPort, ch);
    return ch;
}

/**
 * writes string to log output (stdout / file)
 * @param fmt - format string
 * @param ... - variadic params
 */
void Log::Write(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // format the string with formatting arguments (same as printf)
    fmt(format, args, Log::WriteChar);

    va_end(args);
}