.intel_syntax noprefix

.extern InterruptCommonHandler

.macro isr_err num # interrupt with error code (pushed to the stack)
    .global isr_\num
    .type isr_\num, @function
    isr_\num:
        cli
        push \num # push interrupt number
        jmp common_stub
.endm

.macro isr num # interrupt without error code
    .global isr_\num
    .type isr_\num, @function
    isr_\num:
        cli
        push 0 # push fake error code
        push \num # push interrupt number
        jmp common_stub
.endm

.macro irq num # hardware interrupt without error code
    .global irq_\num
    .type irq_\num, @function
    irq_\num:
        cli
        push 0 # push fake error code
        push \num # push interrupt number
        jmp common_stub
.endm


.global common_stub
.type common_stub, @function
common_stub:
    # the common stub save cpu state (registers)
    # then call to the common handler (cpp function)
    # and in the return it cleans the stack and restore it to what it was before the whole ISR

    pushad # save general registers

    mov eax, ds
    push eax # push current data segment selector

    call InterruptCommonHandler # call the common handler at isr/isr.cpp

    pop eax
    mov ds, eax # restore data segment selector

    popad # restore general registers

    add esp, 8 # clear interrupt number and error code from the stack

    sti # enable again interrupts
    iret # pops cs, eip eflags and error code

# declare ISR macros
isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr_err 8
isr 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr 15
isr 16
isr_err 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

# declare IRQ macros
irq 32
irq 33
irq 34
irq 35
irq 36
irq 37
irq 38
irq 39
irq 40
irq 41
irq 42
irq 43
irq 44
irq 45
irq 46
irq 47
irq 48
