#![no_main]
#![no_std]

#[macro_use]
extern crate user_lib;
use core::arch::asm;

#[no_mangle]
fn main() -> i32 {
    println!("try to execute privileged instruction in U mode");
    println!("kernel should kill this application");
    unsafe {
        asm!("sret");
    }
    0
}
