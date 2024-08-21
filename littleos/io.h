#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/**
sneds the given data to the given i/o port  defined in io.S
 */
void outb(unsigned short port,unsigned char data);

#endif


/**
read a byte from an i/o port
 */
unsigned char inb(unsigned short port);