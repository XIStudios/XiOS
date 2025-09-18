bits 64
global gdt_flush
gdt_flush:
    lgdt [rdi]
    mov ax, 0x10
    mov ds, ax; mov es, ax; mov fs, ax; mov gs, ax; mov ss, ax
    push qword 0x08
    push qword .flush
    retf
.flush:
    ret