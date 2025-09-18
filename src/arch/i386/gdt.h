#ifndef GDT_H
#define GDT_H
#include "include/types.h"
typedef struct { uint16_t limit; uint64_t base; } __attribute__((packed)) GDTPointer;
void gdt_init();
#endif