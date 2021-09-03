.intel_syntax noprefix

.section .text
.global idt_flush
.type idt_flush, @function
idt_flush:
    push ebp
    mov esp, ebp

    mov eax, [ebp + 8] # get idt pointer struct from stack
    lidt [eax] # load the new idt pointer to the idtr register

    pop ebp
    ret