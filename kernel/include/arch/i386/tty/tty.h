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
#include <kernel/logs/logs.h>
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

    constexpr uint8_t kVgaWidth = 80; // line fit 80 characters
    constexpr uint8_t kVgaHeight = 25; // 25 lines in the terminal
    uint16_t* const kTerminalBuffer = (uint16_t*)0xB8000; // buffer location

    static uint8_t terminal_row; // current cursor row location
    static uint8_t terminal_column; // current cursor column location
    static uint8_t terminal_color; // whole terminal color

    void Initialize(); // Initialize terminal screen (Clear and set colors)
    void Clear(); // Clear terminal screen (set all the cells to ' ')
    inline uint8_t VgaEntryColor(enum VgaColor fg, enum VgaColor bg); // translate the color of the foreground and the background to an uint8_t entry usable for the VGA buffer
    inline uint16_t VgaEntry(unsigned char uc, uint8_t color); // translate the color and the char to uint16_t entry usable for the buffer
    void PutEntryAt(char c, uint8_t color, uint8_t x, uint8_t y); // put char with specific color in (x,y) coordinates
    void PutEntryAt(uint16_t entry, uint8_t x, uint8_t y); // overloading for entry parameter
    void PutChar(char c); // put char in current courser location
    void Write(const char* data, size_t size); // write string with size to the terminal
    void WriteString(const char* data); // write string without size to the terminal
    void Scroll(); // scroll down when screen is overflowed
    void IsOverflowed(); // checks if screen is overflowed
};
