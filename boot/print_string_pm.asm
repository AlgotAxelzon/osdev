[bits 32]

; Constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; prints a null-terminated string pointed to by EBX
print_string_pm:
    pusha
    mov ah, WHITE_ON_BLACK
    mov edx, VIDEO_MEMORY   ; Address of current character cell

.loop:
    mov al, [ebx]       ; Store char at EBX in AL
    cmp al, 0           ; If AL == 0, end of string is reached
    je .end             ; jump to .end 

    ;mov ah, WHITE_ON_BLACK
    mov [edx], ax       ; Store char and attributes at current
                        ; character cell
    add ebx, 1          ; Increment EBX to the next char in string
    add edx, 2          ; Move to next character cell in video memory

    jmp .loop
    
.end:
    popa
    ret 

