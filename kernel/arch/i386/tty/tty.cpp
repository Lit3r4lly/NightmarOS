/**
* @file tty.cpp
* @author Ori Feldman
* @brief define tty functions for printing to the screen
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/tty/tty.h>

/**
 * Initialize the TTY component by setting color and clearing the screen
 */
void TTY::Initialize() {
    K_LOG("Initializing TTY");
    K_LOG("Framebuffer address: %x", TTY::kTerminalBuffer);

    terminal_color = VgaEntryColor(VgaColor::kVgaColorWhite, VgaColor::kVgaColorBlack);
    TTY::Clear();

    K_LOG("TTY driver initialized");
}

/**
 * clears the screen with ' ' empty characters
 */
void TTY::Clear() {
    terminal_row = 0;
    terminal_column = 0;

    for (size_t y = 0; y < kVgaHeight; ++y) {
        for (size_t x = 0; x < kVgaWidth; ++x) {
            TTY::PutEntryAt(' ', terminal_color, x, y);
        }
    }

    K_LOG("Cleared terminal screen");
}

/**
 * translate the color of the foreground and the background to an uint8_t entry usable for the VGA buffer
 * @param fg - foreground color, color of the text
 * @param bg - background color
 * @return entry of the colors usable for the buffer
 */
inline uint8_t TTY::VgaEntryColor(enum VgaColor fg, enum VgaColor bg) {
    return static_cast<unsigned int>(fg) | static_cast<unsigned int>(bg) << 4;
}

/**
 * translate the color and the char to uint16_t entry usable for the buffer
 * @param uc - desired character
 * @param color - desired color
 * @return entry of color and character usable for the buffer
 */
inline uint16_t TTY::VgaEntry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

/**
 * put char with specific color in (x,y) coordinates
 * @param c - desired character
 * @param color - desired color
 * @param x - x coordinate (row)
 * @param y - y coordinate (line)
 */
void TTY::PutEntryAt(char c, uint8_t color, uint8_t x, uint8_t y) {
    const size_t index = y * TTY::kVgaWidth + x; // y * kVGA_WIDTH = goes to the start of the column
                                            // and add the offset to this (x)
    TTY::kTerminalBuffer[index] = TTY::VgaEntry(c, color); // insert the entry to the required place
}

/**
 * overloaded function, for entry parameter
 * @param c - desired character
 * @param x - x coordinate (row)
 * @param y - y coordinate (line)
 */
void TTY::PutEntryAt(uint16_t entry, uint8_t x, uint8_t y) {
    const size_t index = y * TTY::kVgaWidth + x; // y * kVGA_WIDTH = goes to the start of the column
                                            // and add the offset to this (x)
    TTY::kTerminalBuffer[index] = entry; // insert the entry to the required place
}

/**
 * puts char in the current courser location
 * @param c - desired character
 */
void TTY::PutChar(char c) {
    if (c == '\n') {
        TTY::terminal_column = 0;
        IsOverflowed();
    } else {
        TTY::PutEntryAt(c, TTY::terminal_color, TTY::terminal_column, TTY::terminal_row);

        if (++TTY::terminal_column == TTY::kVgaWidth) { // if column has reached the limit (end of line)
            TTY::terminal_column = 0;
            IsOverflowed();
        }
    }
}

/**
 * checks if the courser has reached the last line in the terminal
 * if yes, it's scroll down
 */
void TTY::IsOverflowed() {
    if (++TTY::terminal_row == TTY::kVgaHeight) { // if row has reached the limit (end of rows)
        TTY::terminal_row = TTY::kVgaHeight - 1;
        Scroll();
    }
}

/**
 * writes string to the terminal by size
 * @param data - string to be write
 * @param size - size of the string (length)
 */
void TTY::Write(const char* data, size_t size) {
    for (unsigned int i = 0; i < size; ++i)
        TTY::PutChar(data[i]);
}

/**
 * writes string to the terminal
 * @param data - string to be write
 */
void TTY::WriteString(const char* data) {
    TTY::Write(data, ::strlen(data));
}

/**
 * scroll down the terminal by clearing the first line and move all the others once upside
 */
void TTY::Scroll() {
    for (unsigned int x = 0; x < TTY::kVgaWidth; ++x)
        TTY::PutEntryAt(' ', TTY::terminal_color, x, 0); // clears the first row in the terminal

    for (unsigned int y = 1; y < TTY::kVgaHeight; ++y) {
        for (unsigned int x = 0; x < TTY::kVgaWidth; ++x) {
            // set all the lines to one upper line
            TTY::PutEntryAt(TTY::kTerminalBuffer[(y * TTY::kVgaWidth) + x], x, y - 1);
        }
    }
}