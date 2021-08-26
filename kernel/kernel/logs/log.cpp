/**
* @file logs.cpp
* @author Ori Feldman
* @brief this file defines the log system for the OS; using the ports I/O mechanism
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#include <kernel/logs/log.h>

/**
 * writes string to log output (stdout / file)
 * @param data - string to be written
 */
void Log::Write(const char *data) {
    for (unsigned int i = 0; data[i] != '\0'; ++i)
        Ports::OutB(Log::kHackPort, data[i]);
}
