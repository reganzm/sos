#include "io.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5


#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15



/**
move the cursor of the framebuffer to the given position
 */
void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT,FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,((pos>>8) & 0xFF));
    outb(FB_COMMAND_PORT,FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,pos & 0xFF);
}


#define SERIAL_COM1_BASE 0x3F8
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMEND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMEND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)


#define SERIAL_LINE_ENABLE_DLAB 0x80

/**
set the spped of the data being sent. the default speed of a serial port is 115200 bits/s
the argument is a divisor of that number ,hence the resulting speed becomes(115200 / divisor) bits/s
 */
void serial_configure_baud_rate(unsigned short com,unsigned short divisor){
    outb(SERIAL_LINE_COMMEND_PORT(com),SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),(divisor >> 8) & 0xFF);
    outb(SERIAL_DATA_PORT(com),divisor & 0xFF);
}

/**

configures the line of the given serial port ,the port is set to have a data length 8 bit
no parity bits , one stop bit and break contril disabled
 */
void serial_configure_line(unsigned short com){
    outb(SERIAL_LINE_COMMEND_PORT(com),0x03);
}



int serial_is_transmit_fifo_empty(unsigned int com){
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}