/**
* @file keyboard.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 1/13/22
* @copyright Copyright (c) 2022
*/

#include <kernel/keyboard/keyboard.h>

// holds the current specific keyboard driver callback
Keyboard::KeyboardCallback key_source;
Keyboard::Buffer Keyboard::input = {{},0, 0, false};


/**
 * Initialize the keyboard usage (driver specification etc.)
 * @param source_callback - callback function for handling the key receiving
 */
void Keyboard::Initialize(Keyboard::KeyboardCallback source_callback) {
    // TODO: add specification for some drivers (for now only ps2, scan codes (1) is supported)
    Ports::InB(0x60);

    key_source = source_callback;
    ISR::InsertUniqueHandler(33, ISR::Handler {Keyboard::KeyboardHandler, true, true});
}

/**
 * Keyboard interrupt handler (ISR)
 * @param int_num - interrupt number
 * @param stack_state - current stack state (registers etc.)
 */
void Keyboard::KeyboardHandler(uint8_t int_num, ISR::StackState stack_state) {
    Keyboard::InputKeyType key = key_source(nullptr);

    if (key.is_error)
        return;

    if(input.readMode)
        printf("%c", (char)key.character);

    input.insert(key);
}

void Keyboard::read(uint8_t* p, size_t size) {
    if (!p)
        return;

    input.readMode = true;

    while (input.pos - input.readPos < size) {
        asm volatile ("hlt");
    }

    memcpy(p, (input.kinputBuffer + input.readPos), size);

    input.readPos += size;

    input.readMode = false;
}
