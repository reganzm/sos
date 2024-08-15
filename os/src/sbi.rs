use sbi_rt::{legacy, system_reset, NoReason, Shutdown, SystemFailure};

///os call sbi console function to print chars on console
pub fn console_putchar(c: usize) {
    #[allow(deprecated)]
    legacy::console_putchar(c);
}

/// os call sbi shutdown function to shutdown os
pub fn shutdown(failure: bool) -> ! {
    if !failure {
        system_reset(Shutdown, NoReason);
    } else {
        system_reset(Shutdown, SystemFailure);
    }
    unreachable!()
}
