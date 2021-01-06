#include "../kernel/pic.h"
#include "../entry/idt.h"

#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

struct IDTDescr {
    unsigned short int offset_1;    // offset bits 0..15
    unsigned short int selector;    // a code segment selector in GDT or LDT
    unsigned char zero;         // unused, set to 0
    unsigned char type_attr;    // type and attributes, see below
    unsigned short int offset_2;    // offset bits 16..31
};

struct IDTDescr IDT[256];

void idt_init()
{
    extern int load_idt();
    extern int irq0();
    extern int irq1();
    extern int irq2();
    extern int irq3();
    extern int irq4();
    extern int irq5();
    extern int irq6();
    extern int irq7();
    extern int irq8();
    extern int irq9();
    extern int irq10();
    extern int irq11();
    extern int irq12();
    extern int irq13();
    extern int irq14();
    extern int irq15();

    unsigned long irq0_address;
    unsigned long irq1_address;
    unsigned long irq2_address;
    unsigned long irq3_address;
    unsigned long irq4_address;
    unsigned long irq5_address;
    unsigned long irq6_address;
    unsigned long irq7_address;
    unsigned long irq8_address;
    unsigned long irq9_address;
    unsigned long irq10_address;
    unsigned long irq11_address;
    unsigned long irq12_address;
    unsigned long irq13_address;
    unsigned long irq14_address;
    unsigned long irq15_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    PIC_remap(PIC1_OFFSET, PIC2_OFFSET);

    // Only enable IRQ1 (Keyboard)
    IRQ_set_mask(0); 
    IRQ_set_mask(1); 
    IRQ_set_mask(2); 
    IRQ_set_mask(3); 
    IRQ_set_mask(4); 
    IRQ_set_mask(5); 
    IRQ_set_mask(6); 
    IRQ_set_mask(7); 
    IRQ_set_mask(8); 
    IRQ_set_mask(9); 
    IRQ_set_mask(10); 
    IRQ_set_mask(11); 
    IRQ_set_mask(12); 
    IRQ_set_mask(13); 
    IRQ_set_mask(14); 
    IRQ_set_mask(15); 
    IRQ_clear_mask(1);


    irq0_address = (unsigned long)irq0;
    IDT[32].offset_1 = irq0_address & 0xffff;
    IDT[32].selector = 0x08;    // Code segment in GDT
    IDT[32].zero = 0;
    IDT[32].type_attr = 0x8e;    // interrupt gate
    IDT[32].offset_2 = (irq0_address & 0xffff0000) >> 16;

    irq1_address = (unsigned long)irq1;

    IDT[33].offset_1 = irq1_address & 0xffff;
    IDT[33].selector = 0x08;    // Code segment in GDT
    IDT[33].zero = 0;
    IDT[33].type_attr = 0x8e;    // interrupt gate
    IDT[33].offset_2 = (irq1_address & 0xffff0000) >> 16;

    irq2_address = (unsigned long)irq2;
    IDT[34].offset_1 = irq2_address & 0xffff;
    IDT[34].selector = 0x08;    // Code segment in GDT
    IDT[34].zero = 0;
    IDT[34].type_attr = 0x8e;    // interrupt gate
    IDT[34].offset_2 = (irq2_address & 0xffff0000) >> 16;

    irq3_address = (unsigned long)irq3;
    IDT[35].offset_1 = irq3_address & 0xffff;
    IDT[35].selector = 0x08;    // Code segment in GDT
    IDT[35].zero = 0;
    IDT[35].type_attr = 0x8e;    // interrupt gate
    IDT[35].offset_2 = (irq3_address & 0xffff0000) >> 16;

    irq4_address = (unsigned long)irq4;
    IDT[36].offset_1 = irq4_address & 0xffff;
    IDT[36].selector = 0x08;    // Code segment in GDT
    IDT[36].zero = 0;
    IDT[36].type_attr = 0x8e;    // interrupt gate
    IDT[36].offset_2 = (irq4_address & 0xffff0000) >> 16;

    irq5_address = (unsigned long)irq5;
    IDT[37].offset_1 = irq5_address & 0xffff;
    IDT[37].selector = 0x08;    // Code segment in GDT
    IDT[37].zero = 0;
    IDT[37].type_attr = 0x8e;    // interrupt gate
    IDT[37].offset_2 = (irq5_address & 0xffff0000) >> 16;

    irq6_address = (unsigned long)irq6;
    IDT[38].offset_1 = irq6_address & 0xffff;
    IDT[38].selector = 0x08;    // Code segment in GDT
    IDT[38].zero = 0;
    IDT[38].type_attr = 0x8e;    // interrupt gate
    IDT[38].offset_2 = (irq6_address & 0xffff0000) >> 16;

    irq7_address = (unsigned long)irq7;
    IDT[39].offset_1 = irq7_address & 0xffff;
    IDT[39].selector = 0x08;    // Code segment in GDT
    IDT[39].zero = 0;
    IDT[39].type_attr = 0x8e;    // interrupt gate
    IDT[39].offset_2 = (irq7_address & 0xffff0000) >> 16;

    irq8_address = (unsigned long)irq8;
    IDT[40].offset_1 = irq8_address & 0xffff;
    IDT[40].selector = 0x08;    // Code segment in GDT
    IDT[40].zero = 0;
    IDT[40].type_attr = 0x8e;    // interrupt gate
    IDT[40].offset_2 = (irq8_address & 0xffff0000) >> 16;

    irq9_address = (unsigned long)irq9;
    IDT[41].offset_1 = irq9_address & 0xffff;
    IDT[41].selector = 0x08;    // Code segment in GDT
    IDT[41].zero = 0;
    IDT[41].type_attr = 0x8e;    // interrupt gate
    IDT[41].offset_2 = (irq9_address & 0xffff0000) >> 16;

    irq10_address = (unsigned long)irq10;
    IDT[42].offset_1 = irq10_address & 0xffff;
    IDT[42].selector = 0x08;    // Code segment in GDT
    IDT[42].zero = 0;
    IDT[42].type_attr = 0x8e;    // interrupt gate
    IDT[42].offset_2 = (irq10_address & 0xffff0000) >> 16;

    irq11_address = (unsigned long)irq11;
    IDT[43].offset_1 = irq11_address & 0xffff;
    IDT[43].selector = 0x08;    // Code segment in GDT
    IDT[43].zero = 0;
    IDT[43].type_attr = 0x8e;    // interrupt gate
    IDT[43].offset_2 = (irq11_address & 0xffff0000) >> 16;

    irq12_address = (unsigned long)irq12;
    IDT[44].offset_1 = irq12_address & 0xffff;
    IDT[44].selector = 0x08;    // Code segment in GDT
    IDT[44].zero = 0;
    IDT[44].type_attr = 0x8e;    // interrupt gate
    IDT[44].offset_2 = (irq12_address & 0xffff0000) >> 16;

    irq13_address = (unsigned long)irq13;
    IDT[45].offset_1 = irq13_address & 0xffff;
    IDT[45].selector = 0x08;    // Code segment in GDT
    IDT[45].zero = 0;
    IDT[45].type_attr = 0x8e;    // interrupt gate
    IDT[45].offset_2 = (irq13_address & 0xffff0000) >> 16;

    irq14_address = (unsigned long)irq14;
    IDT[46].offset_1 = irq14_address & 0xffff;
    IDT[46].selector = 0x08;    // Code segment in GDT
    IDT[46].zero = 0;
    IDT[46].type_attr = 0x8e;    // interrupt gate
    IDT[46].offset_2 = (irq14_address & 0xffff0000) >> 16;

    irq15_address = (unsigned long)irq15;
    IDT[47].offset_1 = irq15_address & 0xffff;
    IDT[47].selector = 0x08;    // Code segment in GDT
    IDT[47].zero = 0;
    IDT[47].type_attr = 0x8e;    // interrupt gate
    IDT[47].offset_2 = (irq15_address & 0xffff0000) >> 16;


    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDTDescr) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}
