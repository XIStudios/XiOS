#include "mouse.h"
#include "arch/i386/idt.h"
#include "include/io.h"
#include "include/types.h"
volatile int32_t mouse_x = 0; volatile int32_t mouse_y = 0;
static uint8_t mouse_cycle = 0; static int8_t mouse_byte[3];
void mouse_wait(uint8_t type) { uint32_t timeout=100000; if(type==0){while(timeout--){if((inb(0x64)&1)==1)return;}}else{while(timeout--){if((inb(0x64)&2)==0)return;}}}
void mouse_write(uint8_t write){mouse_wait(1);outb(0x64,0xD4);mouse_wait(1);outb(0x60,write);}
uint8_t mouse_read(){mouse_wait(0);return inb(0x60);}
static void mouse_callback(registers_t* regs) {
    (void)regs; uint8_t scancode = inb(0x60);
    switch(mouse_cycle){case 0:mouse_byte[0]=scancode;if(!(scancode&0x08))return;mouse_cycle++;break;case 1:mouse_byte[1]=scancode;mouse_cycle++;break;case 2:mouse_byte[2]=scancode;int32_t dx=mouse_byte[1];int32_t dy=mouse_byte[2];if(mouse_byte[0]&0x10)dx|=0xFFFFFF00;if(mouse_byte[0]&0x20)dy|=0xFFFFFF00;mouse_x+=dx;mouse_y-=dy;if(mouse_x<0)mouse_x=0;if(mouse_y<0)mouse_y=0;if(mouse_x>1023)mouse_x=1023;if(mouse_y>767)mouse_y=767;mouse_cycle=0;break;}
}
void mouse_init() {
    uint8_t status; mouse_wait(1); outb(0x64, 0xA8); mouse_wait(1); outb(0x64, 0x20); mouse_wait(0); status = (inb(0x60) | 2);
    mouse_wait(1); outb(0x64, 0x60); mouse_wait(1); outb(0x60, status); mouse_write(0xF6); mouse_read(); mouse_write(0xF4); mouse_read();
    register_interrupt_handler(44, &mouse_callback);
}