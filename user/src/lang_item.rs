use crate::println;

#[panic_handler]
fn panic_handler(panic_info: &core::panic::PanicInfo) -> ! {
    let err = panic_info.message().as_str().unwrap();
    if let Some(location) = panic_info.location() {
        println!(
            "Panicked as {}:{} , {}",
            location.file(),
            location.line(),
            err
        )
    } else {
        println!("Panicked:{}", err)
    }
    loop {}
}
