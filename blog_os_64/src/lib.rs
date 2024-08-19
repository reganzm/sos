#![no_std]
#![feature(lang_items)]

extern crate rlibc;

use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn rust_main() {
    let x = ["hello", "world", "!"];
    let y = x;
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}

#[lang = "panic_fmt"]
#[no_mangle]
pub extern "C" fn panic_fmt() -> ! {
    loop {}
}
