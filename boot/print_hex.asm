; bx - value to print
print_hex:
    pusha
    mov cx, 5           ; cx - HEX_OUT offset 
    mov ax, bx          ; ax - toPrint
.loop:
    cmp ax, 0           ; is ax == 0?
    je .end
    mov dx, ax
    and dx, 0xF         ; mask least significant nibble
    mov bx, dx
    mov dx, [HEX_TABLE + bx]    ; get ascii-code nibble 
    mov bx, cx
    mov [HEX_OUT + bx], dl      ; store ascii-value in HEX_OUT buffer 
    shr ax, 4           ; shift to remove already parsed nibble
    dec cx              ; dec buffer pointer offset
    jmp .loop
.end:
    mov bx, HEX_OUT
    call print_string
    popa
    ret

; data
HEX_TABLE:
    db '0123456789abcdef'
HEX_OUT:
    db '0x0000', 0

