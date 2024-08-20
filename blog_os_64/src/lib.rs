#![no_std]
#![feature(lang_items)]
#![feature(ptr_internals)]

extern crate alloc;
extern crate multiboot2;
extern crate volatile;

mod allocator;
mod vga_buffer;
mod memory;

use alloc::format;
use core::panic::PanicInfo;
use multiboot2::{BootInformation, BootInformationHeader, MemoryAreaTypeId};

#[no_mangle]
pub extern "C" fn rust_main(multiboot_information_address: usize) {
    vga_buffer::clear_screen();

    let boot_info = unsafe {
        BootInformation::load(multiboot_information_address as *const BootInformationHeader)
            .unwrap()
    };

    let memory_tag_map = boot_info
        .memory_map_tag()
        .expect("elf-sections tag requred");

    // use the max memeory as kernel memory

    let mut kernel_start: u64 = 0;
    let mut kernel_end: u64 = 0;
    let mut size: u64 = 0;

    for section in memory_tag_map.memory_areas() {
        println!(
            "start:{:x} end:{:x} ,type:{:#?},size:{}",
            section.start_address(),
            section.end_address(),
            section.typ(),
            section.size()
        );
        if section.size() > size {
            kernel_start = section.start_address();
            kernel_end = section.end_address();
            size = section.size();
        }
    }

    let multiboot_start = multiboot_information_address;
    let multiboot_end = multiboot_start + (boot_info.total_size() as usize);
    println!(
        "multiboot start:{:x} end:{:x}",
        multiboot_start, multiboot_end
    );

    println!("kernel start:{:x} end:{:x}", kernel_start, kernel_end);
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("PANIC :{:#?}", info);
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}
