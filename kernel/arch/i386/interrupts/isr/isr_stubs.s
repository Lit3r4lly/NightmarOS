.intel_syntax noprefix

.extern InterruptCommonHandler
.extern IrqForwardHandler

.equ KERNEL_CODE_SELECTOR, 0x08
.equ KERNEL_DATA_SELECTOR, 0x10

.macro isr_noerr isr_no
  .globl isr_\isr_no
  .type isr_\isr_no, @function
  isr_\isr_no:
    cli
    push 0x0 # fake error code
    push \isr_no
    jmp isr_common
.endm

.macro isr_err isr_no
  .globl isr_\isr_no
  .type isr_\isr_no, @function
  isr_\isr_no:
    cli
    push \isr_no
    jmp isr_common
.endm

.macro irq irq_no, isr_no
  .globl irq_\irq_no
  .type irq_\irq_no, @function
  irq_\irq_no:
    cli
    push 0x0 # fake error code
    push \isr_no
    jmp irq_common
.endm

.globl isr_common
.type isr_common, @function
isr_common:
    pushad
    mov ax, ds
    push eax
    mov ax, KERNEL_DATA_SELECTOR

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call InterruptCommonHandler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad
    add esp, 8
    sti
    iret

.globl irq_common
.type irq_common, @function
irq_common:
	pushad

	mov ax, ds
	push eax

	mov ax, KERNEL_DATA_SELECTOR
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call IrqForwardHandler

	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popad
	add esp, 8
	sti
	iret

isr_noerr 0
isr_noerr 1
isr_noerr 2
isr_noerr 3
isr_noerr 4
isr_noerr 5
isr_noerr 6
isr_noerr 7
isr_err   8
isr_noerr 9
isr_err   10
isr_err   11
isr_err   12
isr_err   13
isr_err   14
isr_noerr 15
isr_noerr 16
isr_err   17
isr_noerr 18
isr_noerr 19
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_err   30
isr_noerr 31
irq       0,  32
irq       1,  33
irq       2,  34
irq       3,  35
irq       4,  36
irq       5,  37
irq       6,  38
irq       7,  39
irq       8,  40
irq       9,  41
irq       10, 42
irq       11, 43
irq       12, 44
irq       13, 45
irq       14, 46
irq       15, 47