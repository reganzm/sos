use core::ptr::null_mut;

use alloc::alloc::GlobalAlloc;
#[global_allocator]
static ALLOCATOR: Dummy = Dummy;

pub struct Dummy;
unsafe impl GlobalAlloc for Dummy {
    unsafe fn alloc(&self, layout: core::alloc::Layout) -> *mut u8 {
        null_mut()
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: core::alloc::Layout) {
        panic!("dealloc should be never called")
    }
}
