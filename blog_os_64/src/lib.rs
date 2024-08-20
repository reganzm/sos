#![no_std]
#![feature(lang_items)]
#![feature(ptr_internals)]

extern crate volatile;

mod vga_buffer;

use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn rust_main() {
    vga_buffer::clear_screen();
    println!("hello world{}", "!");

    println!("{}", {
        println!("inner");
        "outer"
    });

    loop {}
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}
