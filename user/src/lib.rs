#![no_std]
#![feature(linkage)]

mod lang_item;
mod syscall;
#[macro_use]
pub mod console;

use syscall::*;

#[no_mangle]
#[link_section = ".text.entry"]
pub extern "C" fn _start() -> ! {
    clear_bss();
    exit(main());
    panic!("unreachable after sys_exit!");
}

// tell linker this is a week linkage
#[linkage = "weak"]
#[no_mangle]
fn main() -> i32 {
    panic!("Cannot find main!")
}

fn clear_bss() {
    // call externel c function
    extern "C" {
        fn start_bss();
        fn end_bss();
    }
    // compilor will search globle symbol , that provided by link script linker.ld
    // sbss point to .sbss , ebss point to .ebss
    (start_bss as usize..end_bss as usize).for_each(|e| unsafe { (e as *mut u8).write_volatile(0) })
}

pub fn write(fd: usize, buffer: &[u8]) -> isize {
    sys_write(fd, buffer)
}

pub fn exit(exit_code: i32) -> isize {
    sys_exit(exit_code)
}
