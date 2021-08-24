//
// Created by ori on 8/3/21.
//
#pragma once

// Project headers
#include <kernel/kdefines.h>
#include <libc/string.h>

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

constexpr size_t kVGA_WIDTH = 80; // line fit 80 characters
constexpr size_t kVGA_HEIGHT = 25; // 25 lines in the terminal
uint16_t* const kTerminalBuffer = (uint16_t*)0xB8000; // buffer location

static size_t terminal_row; // current cursor row location
static size_t terminal_column; // current cursor column location
static uint8_t terminal_color; // whole terminal color

namespace TTY {
    void Initialize(); // Initialize terminal screen (Clear and set colors)
    void Clear(); // Clear terminal screen (set all of the cells to ' ')
    inline uint8_t VgaEntryColor(enum VgaColor fg, enum VgaColor bg); // translate the color of the foreground and the background to an uint8_t entry usable for the VGA buffer
    inline uint16_t VgaEntry(uchar uc, uint8_t color); // translate the color and the char to uint16_t entry usable for the buffer
    void PutEntryAt(char c, uint8_t color, size_t x, size_t y); // put char with specific color in (x,y) coordinates
    void PutEntryAt(uint16_t entry, size_t x, size_t y); // overloading for entry paramter
    void PutChar(char c); // put char in current courser location
    void Write(const char* data, size_t size); // write string with size to the terminal
    void WriteString(const char* data); // write string without size to the terminal
    void Scroll(); // scroll down when screen is overflowed
    void IsOverflowed(); // checks if screen is overflowed
};
