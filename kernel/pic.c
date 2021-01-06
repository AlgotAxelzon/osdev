#include "../kernel/low_level.h"
#include "../kernel/pic.h"

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

#define ICW1_ICW4	    0x01    /* ICW4 (not) needed */
#define ICW1_SINGLE	    0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04    /* Call address interval 4 (8) */
#define ICW1_LEVEL	    0x08    /* Level triggered (edge) mode */
#define ICW1_INIT	    0x10    /* Initialization - required! */
 
#define ICW4_8086	    0x01    /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	    0x02    /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08    /* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C    /* Buffered mode/master */
#define ICW4_SFNM	    0x10    /* Special fully nested (not) */

#define PIC_EOI		    0x20    /* End-of-interrupt command code */

// End of interrupt 
void PIC_sendEOI(unsigned char irq)
{
    if(irq >= 8)
    {
        port_byte_out(PIC2_COMMAND,PIC_EOI);
    }
    port_byte_out(PIC1_COMMAND,PIC_EOI);
}

void PIC_remap(int offset1, int offset2)
{
    // Save masks
    unsigned char a1, a2;
    a1 = port_byte_in(PIC1_DATA);
    a2 = port_byte_in(PIC2_DATA);

    // Init sequence
    port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    port_byte_out(PIC1_DATA, offset1);
    port_byte_out(PIC2_DATA, offset2);

    port_byte_out(PIC1_DATA, 4);
    port_byte_out(PIC2_DATA, 2);

    port_byte_out(PIC1_DATA, ICW4_8086);
    port_byte_out(PIC2_DATA, ICW4_8086);

    // Restore masks
    port_byte_out(PIC1_DATA, a1);
    port_byte_out(PIC2_DATA, a2);
}

#define PIC_READ_IRR    0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR    0x0b    /* OCW3 irq service next CMD read */
 
/* Helper func */
static unsigned short int __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    port_byte_out(PIC1_COMMAND, ocw3);
    port_byte_out(PIC2_COMMAND, ocw3);
    return (port_byte_in(PIC2_COMMAND) << 8) | port_byte_in(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
unsigned short int PIC_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
unsigned short int PIC_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

void IRQ_set_mask(unsigned char IRQline) 
{
    unsigned short int port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = port_byte_in(port) | (1 << IRQline);
    port_byte_out(port, value);        
}
 
void IRQ_clear_mask(unsigned char IRQline) 
{
    unsigned short int port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = port_byte_in(port) & ~(1 << IRQline);
    port_byte_out(port, value);        
}
