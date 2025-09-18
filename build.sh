#!/bin/bash
set -e

export CC="x86_64-linux-gnu-gcc"
export LD="x86_64-linux-gnu-ld"
export NASM="nasm"
export KERNEL_NAME="xios.kernel"
LIMINE_SHARE_PATH="build/limine_install/share/limine"
LIMINE_BIN_PATH="build/limine_install/bin"

C_SOURCES="src/core/kmain.c \
           src/drivers/graphics.c \
           src/drivers/mouse.c \
           src/arch/i386/gdt.c \
           src/arch/i386/idt.c"

ASM_SOURCES="src/arch/i386/start.asm \
             src/arch/i386/gdt_asm.asm \
             src/arch/i386/idt_asm.asm"

echo "--- Building XiOS (64-bit) ---"
rm -rf build/iso_root
mkdir -p build/iso_root/boot

wget https://codeberg.org/limine/limine/raw/branch/v7.x/limine.h -O src/include/limine.h

OBJS=""
for src in $ASM_SOURCES; do
    obj_name=$(basename "$src" .asm).o; "$NASM" -f elf64 "$src" -o "build/$obj_name"; OBJS="$OBJS build/$obj_name"
done
for src in $C_SOURCES; do
    obj_name=$(basename "$src" .c).o; "$CC" -I./src/ -c "$src" -o "build/$obj_name" -m64 -ffreestanding -O2 -Wall -Wextra -std=gnu99 -fno-pie -mcmodel=kernel; OBJS="$OBJS build/$obj_name"
done

"$LD" -T src/arch/i386/linker.ld -o "build/iso_root/boot/$KERNEL_NAME" $OBJS -no-pie

cp -v limine.cfg build/iso_root/boot/
cp -v "$LIMINE_SHARE_PATH/limine-bios-cd.bin" \
      "$LIMINE_SHARE_PATH/limine-uefi-cd.bin" \
      "$LIMINE_SHARE_PATH/limine-bios.sys" \
      build/iso_root/boot/
xorriso -as mkisofs -b boot/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label build/iso_root -o build/xios.iso
"$LIMINE_BIN_PATH/limine" bios-install build/xios.iso

echo "--- XiOS Build Complete! ---"