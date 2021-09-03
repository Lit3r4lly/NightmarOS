.intel_syntax noprefix

.section .text
.global isr_common_handler
isr_common_handler:
    pushad ; save general registers

    mov eax, ds
    push eax ; push current data segment selector

    mov ebx, cs
    push ebx ; push current code segment selector

    ; call to isr handler

    pop eax
    mov ds, eax ; restore data segment selector

    popad ; restore general registers

    sti
    iret ; pops cs, eip eflags and error code

