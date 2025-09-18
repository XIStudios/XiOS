#include "arch/i386/gdt.h"
typedef struct { uint16_t limit_low; uint16_t base_low; uint8_t base_middle; uint8_t access; uint8_t granularity; uint8_t base_high; } __attribute__((packed)) GDTEntry;
GDTEntry gdt[3];
GDTPointer gdt_ptr;
extern void gdt_flush(GDTPointer*);
void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF); gdt[num].base_middle = (base >> 16) & 0xFF; gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF); gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0); gdt[num].access = access;
}
void gdt_init() {
    gdt_ptr.limit = (sizeof(GDTEntry) * 3) - 1; gdt_ptr.base  = (uint64_t)&gdt;
    gdt_set_entry(0, 0, 0, 0, 0); gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xA0); gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xC0);
    gdt_flush(&gdt_ptr);
}