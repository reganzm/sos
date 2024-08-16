use riscv::register::sstatus::{self, Sstatus, SPP};

#[repr(C)]
pub struct TrapContext {
    pub x: [usize; 32],   // general regs[0..31]
    pub sstatus: Sstatus, //CSR sstatus
    pub sepc: usize,      //CSR sepc
}

impl TrapContext {
    pub fn set_sp(&mut self, sp: usize) {
        self.x[2] = sp; // 0~31 -> x0~x31  x10~x17 -> a0->a7(a7 save sys_call number)  x1->ra return value x2->sp stack pointer
    }

    /// init app context
    pub fn app_init_context(entry: usize, sp: usize) -> Self {
        let mut sstatus = sstatus::read(); // CSR sstatus
        sstatus.set_spp(SPP::User); // set previous privilege mod to user mode
        let mut cx = Self {
            x: [0; 32],
            sstatus,
            sepc: entry,
        };
        cx.set_sp(sp); // app user stack pointer
        cx
    }
}
