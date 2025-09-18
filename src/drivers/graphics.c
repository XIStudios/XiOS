#include "graphics.h"
static uint32_t* framebuffer; static uint16_t screen_width; static uint16_t screen_height; static uint16_t screen_pitch;
void graphics_init(volatile struct limine_framebuffer_request* fb_req) {
    if (fb_req == 0 || fb_req->response == 0 || fb_req->response->framebuffer_count < 1) { while(1) { asm volatile("hlt"); } }
    struct limine_framebuffer* fb = fb_req->response->framebuffers[0];
    framebuffer = (uint32_t*)fb->address; screen_width = fb->width; screen_height = fb->height; screen_pitch = fb->pitch;
}
void clear_screen_color(uint32_t color) {
    for (uint16_t y = 0; y < screen_height; y++) { for (uint16_t x = 0; x < screen_width; x++) { framebuffer[x + y * (screen_pitch / 4)] = color; } }
}
void draw_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < screen_width && y >= 0 && y < screen_height) { framebuffer[x + y * (screen_pitch / 4)] = color; }
}
void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int cy = y; cy < (y + height); cy++) { for (int cx = x; cx < (x + width); cx++) { draw_pixel(cx, cy, color); } }
}
