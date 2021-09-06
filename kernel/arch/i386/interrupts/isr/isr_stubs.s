.intel_syntax noprefix

.macro isr_err num
    .global isr_\num
    .type isr_\num, @function
    isr_\num:
        cli
        ;...
.endm

.global isr_common
.type isr_common, @function
isr_common:
    pushad ; save general registers

    mov eax, ds
    push eax ; push current data segment selector



    ; call to isr handler

    pop eax
    mov ds, eax ; restore data segment selector

    popad ; restore general registers

    sti
    iret ; pops cs, eip eflags and error code

