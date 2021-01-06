[bits 32]
[extern _start]
[extern idt_init]

call idt_init
call _start
jmp $ 

%include "kernel/irq_caller.asm"
