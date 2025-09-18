bits 64
section .text
global start
extern kmain
start:
    call kmain
    cli
    hlt
