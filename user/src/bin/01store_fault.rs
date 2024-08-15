#![no_main]
#![no_std]

#[macro_use]
extern crate user_lib;

#[no_mangle]
fn main() -> i32 {
    println!("into stored fault,we will insert an invalid store operation...");
    println!("kernel should kill this application!");
    unsafe {
        core::ptr::null_mut::<u8>().write_volatile(0);
    }
    0
}
