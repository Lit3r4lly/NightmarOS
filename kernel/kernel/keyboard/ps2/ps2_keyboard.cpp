/**
* @file ps2_keyboard.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 1/13/22
* @copyright Copyright (c) 2022
*/

#include <kernel/keyboard/ps2/ps2_keyboard.h>

// keys descriptors array for mnemonics
PS2Keyboard::KeyDescriptor keys_descriptors[] = {
        {'`', "Excape Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kEscape},
        {'1', "1 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'2', "2 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'3', "3 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'4', "4 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'5', "5 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'6', "6 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'7', "7 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'8', "8 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'9', "9 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'0', "0 Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'-', "- Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'+', "+ Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Backspace Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kBackspace},
        {'\0', "Tab Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kTab},
        {'Q', "Q Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'W', "W Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'E', "E Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'R', "R Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'T', "T Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'Y', "Y Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'U', "U Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'I', "I Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'O', "O Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'P', "P Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'[', "[ Pressed", PS2Keyboard::KeyStatus::kPressed},
        {']', "] Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Enter Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kEnter},
        {'\0', "Left Control Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kLeftControl},
        {'A', "A Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'S', "S Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'D', "D Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'F', "F Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'G', "G Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'H', "H Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'J', "J Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'K', "K Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'L', "L Pressed", PS2Keyboard::KeyStatus::kPressed},
        {';', "; Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\'', "\' Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'`', "` Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Left Shift Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kLeftShift},
        {'\\', "\\ Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'Z', "Z Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'X', "X Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'C', "C Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'V', "V Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'B', "B Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'N', "N Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'M', "M Pressed", PS2Keyboard::KeyStatus::kPressed},
        {',', ", Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'.', ". Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'/', "/ Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Right Shift Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kRightShift},
        {'*', "* Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Left Alt Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kLeftAlt},
        {' ', "Space Pressed", PS2Keyboard::KeyStatus::kPressed},
        {'\0', "Caps Lock Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kCapsLock},
        {'1', "F1 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'2', "F2 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'3', "F3 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'4', "F4 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'5', "F5 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'6', "F6 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'7', "F7 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'8', "F8 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'9', "F9 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'0', "F10 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey},
        {'-', "F11 Pressed", PS2Keyboard::KeyStatus::kPressed, PS2Keyboard::SpecialCharacterType::kFKey}
};

/**
 * Handles the receiving of the input key
 * @param args - optional arguments (for future implementation of other drivers)
 * @return struct with mnemonics of the key
 */
Keyboard::InputKeyType PS2Keyboard::KeyboardSource(void* args) {
    Keyboard::InputKeyType output_key;

    uint8_t input = Ports::InB(PS2Keyboard::kDataPort);

    // check if input is valid
    if (input > 0 && input < (sizeof(keys_descriptors) / sizeof(keys_descriptors[0]))) {
        auto key = keys_descriptors[input - 1]; // Scan Codes (1) - indexing keys from 1

        K_LOG("PS/2 Keyboard - Recived [%c] - %s", key.value, key.explanation);

        switch (key.special_type)
        {
            case SpecialCharacterType::kEnter:
                output_key.character = '\n';
                break;

            case SpecialCharacterType::kBackspace:
                output_key.character = '\b';
                break;

            default:
                output_key.character = key.value;
                break;
        }
    } else {
        output_key.is_error = true;
    }

    return output_key;
}

