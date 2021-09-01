/**
* @file tty.h
* @author Ori Feldman
* @brief declare tty methods, enums and variables
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#pragma once

// Project headers
#include <kernel/common/kdefines.h>
#include <kernel/logs/log.h>
#include <libc/string.h>

namespace TTY {
    // Hardware text mode color constants.
    enum class VgaColor {
        kVgaColorBlack,
        kVgaColorBlue,
        kVgaColorGreen,
        kVgaColorCyan,
        kVgaColorRed,
        kVgaColorMagenta,
        kVgaColorBrown,
        kVgaColorLightGray,
        kVgaColorDarkGray,
        kVgaColorLightBlue,
        kVgaColorLightGreen,
        kVgaColorLightCyan,
        kVgaColorLightRed,
        kVgaColorLightMagenta,
        kVgaColorLightBrown,
        kVgaColorWhite
    };

    constexpr u8int kVgaWidth = 80; // line fit 80 characters
    constexpr u8int kVgaHeight = 25; // 25 lines in the terminal
    u16int* const kTerminalBuffer = (u16int*)0xB8000; // buffer location

    static u8int terminal_row; // current cursor row location
    static u8int terminal_column; // current cursor column location
    static u8int terminal_color; // whole terminal color

    void Initialize(); // Initialize terminal screen (Clear and set colors)
    void Clear(); // Clear terminal screen (set all of the cells to ' ')
    inline u8int VgaEntryColor(enum VgaColor fg, enum VgaColor bg); // translate the color of the foreground and the background to an uint8_t entry usable for the VGA buffer
    inline u16int VgaEntry(uchar uc, u8int color); // translate the color and the char to uint16_t entry usable for the buffer
    void PutEntryAt(char c, u8int color, u8int x, u8int y); // put char with specific color in (x,y) coordinates
    void PutEntryAt(u16int entry, u8int x, u8int y); // overloading for entry paramter
    void PutChar(char c); // put char in current courser location
    void Write(const char* data, size_t size); // write string with size to the terminal
    void WriteString(const char* data); // write string without size to the terminal
    void Scroll(); // scroll down when screen is overflowed
    void IsOverflowed(); // checks if screen is overflowed
};
