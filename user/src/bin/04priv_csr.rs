#![no_main]
#![no_std]

#[macro_use]
extern crate user_lib;

use riscv::register::sstatus::{self, SPP};

#[no_mangle]
fn main() -> i32 {
    println!("try to access privileged CSR in U Mode");
    println!("kernel should kill this application");
    unsafe {
        sstatus::set_spp(SPP::User);
    }
    0
}
