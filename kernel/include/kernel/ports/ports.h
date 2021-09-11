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
    inline u8int InB(const u16int port) {
        u8int input{};
        asm volatile ("in %%dx, %%al;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * gets word input from port
     * @param port - port number
     * @return input from port (with size of word)
     */
    inline u16int InW(const u16int port) {
        u16int input{};
        asm volatile ("in %%dx, %%ax;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * gets double word input from port
     * @param port - port number
     * @return input from port (with size of double word)
     */
    inline u32int InDw(const u16int port) {
        u32int input{};
        asm volatile ("in %%dx, %%eax;" : "=a"(input) : "d"(port));
        return input;
    }

    /**
     * sends byte output to port
     * @param port - port number
     * @param data - data to be sent (with size of byte)
     */
    inline void OutB(const u16int port, const u8int data) {
        asm volatile ("out %%al, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * sends word output to port
     * @param port - port number
     * @param data - data to be sent (with size of word)
     */
    inline void OutW(const u16int port, const u16int data) {
        asm volatile ("out %%ax, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * sends double output to port
     * @param port - port number
     * @param data - data to be sent (with size of double word)
     */
    inline void OutDw(const u16int port, const u32int data) {
        asm volatile ("out %%eax, %%dx;" : : "a"(data), "d"(port));
    }

    /**
     * wait a very small amount of time (1 to 4 microseconds, generally)
     * */
    inline void IoWait()
    {
        Ports::OutB(0x80, 0);
    }
};
