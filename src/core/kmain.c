#include "include/limine.h"
#include "drivers/graphics.h"
#include "drivers/mouse.h"
#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"
static volatile struct limine_framebuffer_request framebuffer_request = { .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0 };
#define COLOR_DESKTOP_BLUE 0x00003366
#define COLOR_TASKBAR_GRAY 0x00888888
#define COLOR_CURSOR_WHITE 0x00FFFFFF
extern volatile int32_t mouse_x;
extern volatile int32_t mouse_y;
void kmain(void) {
    gdt_init();
    graphics_init(&framebuffer_request);
    idt_init();
    mouse_init();
    asm volatile ("sti");
    while(1) {
        clear_screen_color(COLOR_DESKTOP_BLUE);
        draw_rect(0, 700, 1024, 68, COLOR_TASKBAR_GRAY);
        draw_rect(mouse_x, mouse_y, 3, 3, COLOR_CURSOR_WHITE);
    }
}