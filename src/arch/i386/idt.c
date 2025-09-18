#include "arch/i386/idt.h"
#include "include/io.h"
typedef struct { uint16_t base_low; uint16_t selector; uint8_t ist; uint8_t flags; uint16_t base_mid; uint32_t base_high; uint32_t always0; } __attribute__((packed)) IDTEntry;
typedef struct { uint16_t limit; uint64_t base; } __attribute__((packed)) IDTPointer;
IDTEntry idt[256];
IDTPointer idt_ptr;
interrupt_handler_t interrupt_handlers[256];
extern void idt_load(IDTPointer*);
extern void isr44();
void idt_set_entry(uint8_t num, uint64_t base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF; idt[num].base_mid = (base >> 16) & 0xFFFF; idt[num].base_high = (base >> 32) & 0xFFFFFFFF;
    idt[num].selector = selector; idt[num].flags = flags; idt[num].ist = 0; idt[num].always0 = 0;
}
void pic_remap() {
    outb(0x20, 0x11); outb(0xA0, 0x11); outb(0x21, 0x20); outb(0xA1, 0x28); outb(0x21, 0x04); outb(0xA1, 0x02); outb(0x21, 0x01); outb(0xA1, 0x01); outb(0x21, 0x0); outb(0xA1, 0x0);
}
void idt_init() {
    idt_ptr.limit = sizeof(IDTEntry) * 256 - 1; idt_ptr.base = (uint64_t)&idt;
    for (int i = 0; i < 256; i++) interrupt_handlers[i] = 0;
    pic_remap();
    idt_set_entry(44, (uint64_t)isr44, 0x08, 0x8E);
    idt_load(&idt_ptr);
}
void interrupt_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no] != 0) interrupt_handlers[regs->int_no](regs);
    if (regs->int_no >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
void register_interrupt_handler(uint8_t n, interrupt_handler_t handler) {
    interrupt_handlers[n] = handler;
}