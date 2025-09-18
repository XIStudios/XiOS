#ifndef IDT_H
#define IDT_H
#include "include/types.h"
typedef struct { uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rdi, rsi, rbp, rdx, rcx, rbx, rax; uint64_t int_no, err_code; } registers_t;
typedef void (*interrupt_handler_t)(registers_t*);
void idt_init();
void register_interrupt_handler(uint8_t n, interrupt_handler_t handler);
#endif