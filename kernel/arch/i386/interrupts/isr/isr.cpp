/**
* @file isr.cpp
* @author Ori Feldman
* @brief define common isr handler stuff
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/isr/isr.h>

// Described intel exceptions
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

// unique handlers array (used for searching if needed custom handling)
ISR::Handler interrrupts_handlers[ISR::kNumOfEntries] = { nullptr };

/* Control flow described in the header file */

/**
 * initialize interrupts ISRs
 */
void ISR::Initialize() {
    K_LOG("Initializing all unique handlers with nullptr");
    // initialize all interrupt handlers as nullptr
    for (auto& curr : interrrupts_handlers)
        curr = nullptr;
}

/**
 * install custom handler for interrupt (e.g. page-fault for restoring new page)
 * @param int_num - interrupt number
 * @param interrupt_handler - custom interrupt handler
 */
void ISR::InsertUniqueHandler(u8int int_num, ISR::Handler handler) {
    K_LOG("Inserted new unique handler - number: %d, address: %p", int_num, handler);
    interrrupts_handlers[int_num] = handler;
}

/**
 * interrupts common handler - prints the information of the interrupt
 * If there is interrupt that should be handled uniqely, the common handler would call it
 */
extern "C" void ISR::InterruptCommonHandler(ISR::StackState stack_state) {
    auto int_num = stack_state.int_num;
    auto& handler = interrrupts_handlers[int_num];

    // checks if the interrupt is exception and if there is unique handler for it
    // if not -> the exception is unhandled
    if (int_num < ISR::kNumOfExceptions && handler == nullptr) {
        // unhandled exception -> dump registers -> panic
        auto& current_exception = exceptions[int_num];

        printf("[!] Unhandled Exception '#%s - %s' has occurred\n", current_exception.mnemonic, current_exception.description);
        printf("    ERR: %x, NUM: %x \n", stack_state.err_code, int_num);
        printf("    EIP: %x, DS: %x, CS: %x, EFLAGS: %x\n", stack_state.eip, stack_state.ds, stack_state.cs, stack_state.eflags);
        printf("    EAX: %x, EBX: %x, ECX: %x\n", stack_state.eax, stack_state.ebx, stack_state.ecx);
        printf("    EDX: %x, EDI: %x, ESI: %x\n", stack_state.edx, stack_state.edi, stack_state.esi);
        printf("    EBP: %x, ESP: %x\n", stack_state.ebp, stack_state.esp);
        printf("    CR0: %x, CR2: %x, CR3: %x\n", I386::ControlRegisters::cr0(), I386::ControlRegisters::cr2(), I386::ControlRegisters::cr3());

        K_LOG("Unhandled Exception (%x) `#%s - %s` has occurred", int_num, current_exception.mnemonic, current_exception.description)

        while(true)
            asm volatile ("cli; hlt;");
    }

    if (int_num < ISR::kNumOfExceptions && handler != nullptr) {
        // found unique handler for the interrupt (e.g. page-fault handler)
        auto& current_exception = exceptions[int_num];
        K_LOG("Handled Exception (%x) `#%s - %s` has occurred, handler: %p", int_num, current_exception.mnemonic, current_exception.description, handler)

        handler(int_num, stack_state);
    }
}