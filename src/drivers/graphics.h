#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "include/limine.h"
void graphics_init(volatile struct limine_framebuffer_request* fb_req);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void clear_screen_color(uint32_t color);
#endif