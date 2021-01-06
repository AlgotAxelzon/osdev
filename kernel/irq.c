#include "../kernel/low_level.h"
#include "../drivers/screen.h"
#include "../kernel/pic.h"

void irq0_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq1_handler() 
{
    char scancode[2];
    scancode[1] = '\0';
    scancode[0] = port_byte_in(0x60);
    print((char*) &scancode);
    PIC_sendEOI(1);     // EOI
}

void irq2_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq3_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq4_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq5_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq6_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq7_handler() 
{
    // TODO: check if Spurious IRQ 
    PIC_sendEOI(0);     // EOI
}

void irq8_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq9_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq10_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq11_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq12_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq13_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq14_handler() 
{
    PIC_sendEOI(0);     // EOI
}

void irq15_handler()
{
    // TODO: check if Spurious IRQ 
    PIC_sendEOI(0);     // EOI
}
