#![no_main]
// tell compiler there is no std libs
#![no_std]

mod lang_items;

use core::arch::global_asm;
// mixin asm file as str and rust compilor can compile it
global_asm!(include_str!("entry.asm"));

#[no_mangle]
pub fn rust_main() -> ! {
    clear_bss();
    loop {}
}


fn clear_bss(){
    // call externel c function
    extern "C" {
        fn sbss();
        fn ebss();
    }
    // compilor will search globle symbol , that provided by link script linker.ld
    // sbss point to .sbss , ebss point to .ebss
    (sbss as usize .. ebss as usize).for_each(|e|{
        unsafe {
            (e as *mut u8).write_volatile(0)
        }
    })
}