#![no_std]
#![feature(lang_items)]

use core::panic::PanicInfo;

#[no_mangle]
pub extern fn rust_main() {
    let hello = b"Hello World!";

    let color_type = 0x1f;
    let mut hello_colored = [color_type;24];
    for (i,char_byte) in hello.into_iter().enumerate(){
        hello_colored[i*2] = *char_byte;
    }
    let buffer_ptr = (0xb8000+1988) as *mut _;
    unsafe{
        *buffer_ptr = hello_colored;
    }
    loop{}
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}
