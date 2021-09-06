/**
* @file isr.cpp
* @author Ori Feldman
* @brief define common isr handler stuff
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/isr/isr.h>

ISR::IntelExceptions exceptions[ISR::kNumOfExceptions] = {
        {"DE", "Divide-by-zero Error"},
        {"DB", "Debug"},
        {"-", "Non-maskable"},
        {"BP", "Breakpoint"},
        {"OF", "Overflow"},
        {"BR", "Bound Range Exceeded"},
        {"UD", "Invalid Opcode"},
        {"NM", "Coprocessor Not Available"},
        {"DF", "Double Fault"},
        {"-", "Coprocessor Segment Overrun"},
        {"TS", "Invalid TSS"},
        {"NP", "Segment Not Present"},
        {"SS", "Stack-Segment Fault"},
        {"GP", "General Protection Fault"},
        {"PF", "Page Fault"},
        {"-", "[Intel Reserved]"},
        {"MF", "x87 Floating-Point Exception"}
};

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
extern "C" void ISR::InterruptCommonStub(ISR::StackState stack_state) {
    auto int_num = stack_state.int_num;

    // checks if the interrupt is exception and if there is unique handler for it
    // if not -> the exception is unhandled
    if (int_num < 17 && interrrupts_handlers[int_num] != nullptr) {
        auto current_exception = exceptions[int_num];

        printf("[^] Unhandled Exception #%s %s has occurred\n", current_exception.mnemonic, current_exception.description);
        printf("    ERR: %x, NUM: %x \n", stack_state.err_code, int_num);
        printf("    EIP: %x, DS: %x, CS: %x, EFLAGS: %x", stack_state.eip, stack_state.ds, stack_state.cs, stack_state.eflags);
        printf("    EAX: %x, EBX: %x, ECX: %x", stack_state.eax, stack_state.ebx, stack_state.ecx);
        printf("    EDX: %x, EDI: %x, ESI: %x", stack_state.edx, stack_state.edi, stack_state.esi);
        printf("    EBP: %x, ESP: %x", stack_state.ebp, stack_state.esp);

    }
}