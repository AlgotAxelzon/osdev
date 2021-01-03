; load DH  sectors  to ES:BX from  drive  DL
disk_load:
    push dx

    mov ah, 0x02    ; BIOS Read Sectors into Memory function
    mov al, dh      ; Numbers of sectors to read
    mov ch, 0x00    ; Select cylinder 0
    mov dh, 0x00    ; Select head 0
    mov cl, 0x02    ; Read from sector 2
    
    int 0x13        ; BIOS Disk I/O Services

    jc disk_error   ; CF set if error occured
    
    pop dx
    cmp dh, al      ; Compare sectors excpected to sectors read
    jne disk_error2  ; Error if above not equal
    ret

disk_error: 
    mov bx, DISK_ERROR_MSG1
    call print_string       ; Print error message 

    jmp $           ; Hang
disk_error2: 
    mov bx, DISK_ERROR_MSG2
    call print_string       ; Print error message 

    jmp $           ; Hang


DISK_ERROR_MSG1:
    db 'CF set!', 0
DISK_ERROR_MSG2:
    db 'Expected != actual!', 0

