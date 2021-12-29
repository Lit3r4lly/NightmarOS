.intel_syntax noprefix

.global enable_paging
.type enable_paging, @function
enable_paging:
    push ebp
    mov ebp, esp

    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    mov esp, ebp
    pop ebp
    ret

.global load_page_directory
.type load_page_directory, @function
load_page_directory:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov cr3, eax

    mov esp, ebp
    pop ebp
    ret