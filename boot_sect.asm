[org 0x7c00]
KERNEL_OFFSET equ 0x1000    ; Memory offset to which kernel will load

    mov [BOOT_DRIVE], dl    ; Store boot drive

    mov bp, 0x9000          ; Set stack base and pointer
    mov sp, bp
              
    mov bx, MSG_REAL_MODE   ; Print string to inform real mode
    call print_string       ; is active

    call load_kernel        ; Load kernel into memory

    call switch_to_pm       ; Should never return from this call

    jmp $

%include "print/print_string.asm"
%include "hex/print_hex.asm"
%include "disk/disk_load.asm"
%include "pm/gdt.asm"
%include "pm/print_string_pm.asm"
%include "pm/switch_to_pm.asm"

[bits 16]

load_kernel:
    
    mov bx, MSG_LOAD_KERNEL     ; Print message that the kernel is    
    call print_string           ; being loaded

    mov bx, KERNEL_OFFSET       ; Load 15 sectors (the kernel code) 
    mov dh, 2                   ; to KERNEL_OFFSET in memory
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]

BEGIN_PM:
    
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET    

    jmp $

; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0xa, 0xd, 0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0xa, 0xd, 0

; Bootsector padding
times 510-($-$$) db 0
dw 0xaa55
