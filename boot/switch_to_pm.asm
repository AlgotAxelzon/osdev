[bits 16]
; Switch to protected mode
switch_to_pm:
    
    cli                     ; Clear interrupt
    
    lgdt [gdt_descriptor]   ; Load GDT
    
    mov eax, cr0            ; Set first bit in cr0 to
    or eax, 0x1             ; activate protected mode
    mov cr0, eax    

    jmp CODE_SEG:init_pm    ; Long jump to start_protected_mode
                            ; to flush pipe

[bits 32]
; Initiate registers and stack once in PM
init_pm:

    mov ax, DATA_SEG        ; Set segment registers to data selector
    mov ds, ax              ; defined in GDT
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 

    mov ebp, 0x90000        ; Update stack position
    mov esp, ebp

    call BEGIN_PM

