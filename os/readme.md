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

# generated release file
```
cargo build --release
```

# strip metadata
```
rust-objcopy --strip-all target/riscv64gc-unknown-none-elf/release/os -O binary target/riscv64gc-unknown-none-elf/release/os.bin
```

# start gdb-server start experiment
### -s qemu lisent at tcp port 1234 wait for gdbclient to connect
### -S qemu receive request then start run
```
qemu-system-riscv64 -machine virt -nographic -bios ../bootloader/rustsbi-qemu.bin -device loader,file=target/riscv64gc-unknown-none-elf/release/os.bin,addr=0x80200000 -s -S
```
# start gdb-cient connect to gdb-server
```
riscv64-unknown-elf-gdb -ex 'file target/riscv64gc-unknown-none-elf/release/os' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'
```