/**
* @file ports.h
* @author Ori Feldman
* @brief this file declare the I/O operations for ports
* @date 8/26/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>

namespace Ports {
    /**
     * gets byte input from port
     * @param port - port number
     * @return input from port (with size of byte)
     */
    inline uint8_t InB(const uint16_t port) {
        uint8_t input{};
        asm volatile ("in %%dx, %%al;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * gets word input from port
     * @param port - port number
     * @return input from port (with size of word)
     */
    inline uint16_t InW(const uint16_t port) {
        uint16_t input{};
        asm volatile ("in %%dx, %%ax;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * gets double word input from port
     * @param port - port number
     * @return input from port (with size of double word)
     */
    inline uint32_t InDw(const uint16_t port) {
        uint32_t input{};
        asm volatile ("in %%dx, %%eax;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * sends byte output to port
     * @param port - port number
     * @param data - data to be sent (with size of byte)
     */
    inline void OutB(const uint16_t port, const uint8_t data) {
        asm volatile ("out %%al, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * sends word output to port
     * @param port - port number
     * @param data - data to be sent (with size of word)
     */
    inline void OutW(const uint16_t port, const uint16_t data) {
        asm volatile ("out %%ax, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * sends double output to port
     * @param port - port number
     * @param data - data to be sent (with size of double word)
     */
    inline void OutDw(const uint16_t port, const uint32_t data) {
        asm volatile ("out %%eax, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * wait a very small amount of time (1 to 4 microseconds, generally)
     * */
    inline void IoWait() {
        OutB(0x80, 0);
    }
};
