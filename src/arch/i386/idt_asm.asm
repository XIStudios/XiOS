bits 64

; This is the function that our C code calls to load the IDT register.
global idt_load
idt_load:
    ; The pointer to our IDT descriptor is passed as the first argument,
    ; which is in the RDI register in 64-bit mode.
    lgdt [rdi]
    ret

; This tells the assembler that 'interrupt_handler' is a C function
; defined in another file. The linker will connect them.
extern interrupt_handler

; These macros are helpers to save and restore all 64-bit registers.
%macro pushaq 0
    push rax; push rbx; push rcx; push rdx; push rbp; push rsi; push rdi
    push r8; push r9; push r10; push r11; push r12; push r13; push r14; push r15
%endmacro
%macro popaq 0
    pop r15; pop r14; pop r13; pop r12; pop r11; pop r10; pop r9; pop r8
    pop rdi; pop rsi; pop rbp; pop rdx; pop rcx; pop rbx; pop rax
%endmacro

; This is the common code that all our hardware interrupts will run.
isr_common_stub:
    pushaq          ; Save all registers
    mov rdi, rsp    ; Pass a pointer to the saved registers to our C handler
    call interrupt_handler
    popaq           ; Restore all registers
    add rsp, 16     ; Clean up the dummy error code and interrupt number from the stack
    iretq           ; Return from the interrupt

; This macro creates a tiny entry point for a specific interrupt number.
%macro ISR_NOERR 1
global isr%1
isr%1:
    push byte 0      ; Push a dummy error code (for consistency)
    push byte %1     ; Push the interrupt number
    jmp isr_common_stub
%endmacro

; We create the specific stubs that our idt.c file needs.
ISR_NOERR 44 ; For the mouse (IRQ12)