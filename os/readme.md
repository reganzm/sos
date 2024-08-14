# install analysis tools

```
cargo install cargo-binutils
rustup component add llvm-tools-preview
```

# check file format
```
file target/riscv64gc-unknown-none-elf/debug/os
```

# file header info
```
rust-readobj -h target/riscv64gc-unknown-none-elf/debug/os

```
# deassembly 
```
rust-objdump -S target/riscv64gc-unknown-none-elf/debug/os
```