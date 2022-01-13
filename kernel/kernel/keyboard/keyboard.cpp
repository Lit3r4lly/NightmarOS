/**
* @file keyboard.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 1/13/22
* @copyright Copyright (c) 2022
*/

#include <kernel/keyboard/keyboard.h>

Keyboard::KeyboardCallback key_source;

void Keyboard::Initialize(Keyboard::KeyboardCallback source_callback) {
    // TODO: add specification for some drivers (for now only ps2, scan codes (1) is supported)
    Ports::InB(0x60);

    key_source = source_callback;
    ISR::InsertUniqueHandler(33, ISR::Handler {Keyboard::KeyboardHandler, true, true});
}


void Keyboard::KeyboardHandler(uint8_t int_num, ISR::StackState stack_state) {
    Keyboard::InputKeyType key = key_source(nullptr);

    if (key.is_error)
        return;

    printf("%c", (char)key.character);

    // TODO: save input key to some buffer
}