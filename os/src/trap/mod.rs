pub mod context;
use crate::batch::run_next_app;
use crate::syscall::syscall;
use core::arch::global_asm;

use riscv::register::{mtvec::TrapMode,scause::{self,Exception,Trap},stval,stvec};


// the global_asm macro will do static check
global_asm!(include_str!("trap.S"));




