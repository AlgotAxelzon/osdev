; bx - string_ptr
print_string:
    pusha
    mov ah, 0x0e    ; TTY mode
.loop:
    mov al, [bx]    ; move character to al
    cmp al, 0       ; is character == 0 (end of string)
    je .end
    int 0x10        ; call interrupt 10, bios video and screen
    inc bx          ; increment bx, move to next character 
    jmp .loop
.end:
    popa
    ret

