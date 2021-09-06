/**
* @file isr.cpp
* @author Ori Feldman
* @brief define common isr handler stuff
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/isr/isr.h>

ISR::Handler interrrupts_handlers[ISR::kNumOfEntries] = { nullptr };

/* Control flow described in the header file */

/**
 * Initialize interrupts handlers array with nullptr
 */
void ISR::Initialize() {
    // initialize all interrupt handlers as nullptr
    for (Handler& curr : interrrupts_handlers)
        curr = nullptr;
}

/**
 * install custom handler for interrupt (e.g. page-fault for restoring new page)
 * @param interrupt_id - interrupt number
 * @param interrupt_handler - custom interrupt handler
 */
void ISR::InsertUniqueHandler(u8int interrupt_id, ISR::Handler handler) {
    interrrupts_handlers[interrupt_id] = handler;
}

/**
 * interrupts common handler - prints the information of the interrupt
 * If there is interrupt that should be handled uniqely, the common handler would call it
 */
extern "C" void ISR::InterruptCommonStub() {

}