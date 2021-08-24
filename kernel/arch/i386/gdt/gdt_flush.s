.intel_syntax noprefix

.equ KERNEL_CODE_SELECTOR, 0x08
.equ KERNEL_DATA_SELECTOR, 0x10

.section .text
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
    push ebp
    mov ebp, esp
    cli # disable interrupts

    mov eax, [ebp + 8] # copy the parameter into eax
    lgdt [eax] # load the gdtr register with the parameter address

    # move the data segment selector to the data segment registers
    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp KERNEL_CODE_SELECTOR:end # make far jump for inserting into CS the new segment selector
                                # (cannot be accomplished without far jump/call, so needed to jump into "another" segment for updating CS)

end:
    pop ebp
    ret
