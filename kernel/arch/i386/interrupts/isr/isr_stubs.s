.intel_syntax noprefix

.macro isr_err num ; interrupt with error code (pushed to the stack)
    .global isr_\num
    .type isr_\num, @function
    isr_\num:
        cli ; disable interrupts - considered as trap handler
        push \num ; push interrupt number
        jmp common_stub
.endm

.macro isr num ; interrupt without error code
    .global isr_\num
    .type isr_\num, @function
    isr_\num:
        cli ; disable interrupts - considered as trap handler
        push 0 ; push fake error code
        push \num ; push interrupt number
        jmp common_stub
.endm


.global common_stub
.type common_stub, @function
common_stub:
    ; the common stub save cpu state (registers)
    ; then call to the common handler (cpp function)
    ; and in the return it cleans the stack and restore it to what it was before the whole ISR

    pushad ; save general registers

    mov eax, ds
    push eax ; push current data segment selector

    call InterruptCommonHandler ; call the common handler at isr/isr.cpp

    pop eax
    mov ds, eax ; restore data segment selector

    popad ; restore general registers

    add esp, 8 ; clear interrupt number and error code from the stack

    sti ; enable again interrupts (considered as trap handler)
    iret ; pops cs, eip eflags and error code

