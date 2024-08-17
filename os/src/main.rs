#![no_main]
// tell compiler there is no std libs
#![no_std]

mod console;
mod lang_items;
mod sbi;

use core::arch::global_asm;
// mixin asm file as str and rust compilor can compile it
global_asm!(include_str!("entry.asm"));

#[no_mangle]
pub fn rust_main() -> ! {
    clear_bss();
    println!("hello world!");
    panic!("shutdown now!");
}

fn clear_bss() {
    // call externel c function. this is a "C" convention
    // use linker script varaible throuth extern "C" func
    // extern "C" {
    //     fn sbss();
    //     fn ebss();
    // }
    extern "C" {
        static mut sbss: usize;
        static mut ebss: usize;
    }
    // compilor will search globle symbol , that provided by link script linker.ld
    // sbss point to .sbss , ebss point to .ebss
    //(sbss as usize..ebss as usize).for_each(|e| unsafe { (e as *mut u8).write_volatile(0) })
    // another way
    unsafe { (sbss..ebss).for_each(|e| (e as *mut u8).write_volatile(0)) }
}
