#ifndef PIC_H
#define PIC_H

void IRQ_clear_mask(unsigned char IRQline);
void IRQ_set_mask(unsigned char IRQline);
void PIC_sendEOI(unsigned char irq);

void PIC_remap(int offset1, int offset2);

unsigned short int PIC_get_irr(void);
 
unsigned short int PIC_get_isr(void);

#endif
