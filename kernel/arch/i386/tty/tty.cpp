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
    K_LOG("Frame buffer address: %d", TTY::kTerminalBuffer); // TODO: change printing to %x

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
inline u8int TTY::VgaEntryColor(enum VgaColor fg, enum VgaColor bg) {
    return static_cast<uint>(fg) | static_cast<uint>(bg) << 4;
}

/**
 * translate the color and the char to uint16_t entry usable for the buffer
 * @param uc - desired character
 * @param color - desired color
 * @return entry of color and character usable for the buffer
 */
inline u16int TTY::VgaEntry(uchar uc, u8int color) {
    return (u16int)uc | (u16int)color << 8;
}

/**
 * put char with specific color in (x,y) coordinates
 * @param c - desired character
 * @param color - desired color
 * @param x - x coordinate (row)
 * @param y - y coordinate (line)
 */
void TTY::PutEntryAt(char c, u8int color, u8int x, u8int y) {
    const size_t index = y * kVgaWidth + x; // y * kVGA_WIDTH = goes to the start of the column
                                            // and add the offset to this (x)
    kTerminalBuffer[index] = TTY::VgaEntry(c, color); // insert the entry to the required place
}

/**
 * overloaded function, for entry parameter
 * @param c - desired character
 * @param x - x coordinate (row)
 * @param y - y coordinate (line)
 */
void TTY::PutEntryAt(u16int entry, u8int x, u8int y) {
    const size_t index = y * kVgaWidth + x; // y * kVGA_WIDTH = goes to the start of the column
                                            // and add the offset to this (x)
    kTerminalBuffer[index] = entry; // insert the entry to the required place
}

/**
 * puts char in the current courser location
 * @param c - desired character
 */
void TTY::PutChar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        IsOverflowed();
    } else {
        TTY::PutEntryAt(c, terminal_color, terminal_column, terminal_row);

        if (++terminal_column == kVgaWidth) { // if column has reached the limit (end of line)
            terminal_column = 0;
            IsOverflowed();
        }
    }
}

/**
 * checks if the courser has reached the last line in the terminal
 * if yes, it's scroll down
 */
void TTY::IsOverflowed() {
    if (++terminal_row == kVgaHeight) { // if row has reached the limit (end of rows)
        terminal_row = kVgaHeight - 1;
        Scroll();
    }
}

/**
 * writes string to the terminal by size
 * @param data - string to be write
 * @param size - size of the string (length)
 */
void TTY::Write(const char* data, size_t size) {
    for (uint i = 0; i < size; ++i)
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
    for (uint x = 0; x < kVgaWidth; ++x)
        TTY::PutEntryAt(' ', terminal_color, x, 0); // clears the first row in the terminal

    for (uint y = 1; y < kVgaHeight; ++y) {
        for (uint x = 0; x < kVgaWidth; ++x) {
            // set all the lines to one upper line
            TTY::PutEntryAt(kTerminalBuffer[(y * kVgaWidth) + x], x, y - 1);
        }
    }
}