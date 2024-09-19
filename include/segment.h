
#pragma once
// 1 0 00
#define KERNEL_CS 0x8
// 10 0 00
#define KERNEL_DS  0x10
// 11 0 11
#define USER32_CS  0x1b
// 100 0 11 32bit and 64bit is same
#define USER_DS  0x23
#define USER_CS 0x2b
#define USER32_DS USER_DS
// 101 0 11
#define USER64_CS  0x2b

#define GDT_TSS_ENTRY 6