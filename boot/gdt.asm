; GDT
gdt_start:

gdt_null:       ; null descriptor
    dd 0x0 
    dd 0x0

gdt_code:       ; code segment descriptor
    ; limit=0xffff, base=0x0
    ; type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
    ; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
    ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
    dw 0xffff       ; Limit (bits 0-15)
    dw 0x0          ; Base (bits 0-15)
    db 0x0          ; Base (bits 16-23)
    db 10011010b    ; 1st flags, Type flags
    db 11001111b    ; 2nd flags, Limit (bits 16-19)
    db 0x0          ; Base (bits 24-31)

gdt_data:       ; data segment descriptor
    ; Same as code segment except for the type flags:
    ; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
    dw 0xffff       ; Limit (bits 0-15)
    dw 0x0          ; Base (bits 0-15)
    db 0x0          ; Base (bits 16-23)
    db 10010010b    ; 1st flags, Type flags
    db 11001111b    ; 2nd flags, Limit (bits 16-19)
    db 0x0          ; Base (bits 24-31)

gdt_end:        ; Used to calculate GDT size

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of GDT, one less than true size
    dd gdt_start                ; Start address of GDT

; Constants for GDT segment descriptor offsets
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

