// tell compiler there is no main fn
#![no_main]
// tell compiler there is no std libs
#![no_std]


mod lang_items;

use core::arch::global_asm;
// mixin asm file as str and rust compilor can compile it
global_asm!(include_str!("entry.asm"));




