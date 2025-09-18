ENTRY(start)
OUTPUT_FORMAT(elf64-x86-64)
SECTIONS {
    . = 0xFFFFFFFF80000000;
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}