# NOTES
- The command `nm <binary>` will tell you which symbols in the binary are defined and, more importantly for our purpose, which symbols are used by the given binary. 
- How to recognize system call in assembly output with objdump? Here is an example:
  ```
    call   0x55555555c0b0 <syscall@plt>.
  ```
  where
  ```
    0000000000006080 <syscall@plt>:
    6080:	ff 25 a2 2f 06 00    	jmp    QWORD PTR [rip+0x62fa2]        # 69028 <syscall@GLIBC_2.2.5>
    6086:	68 05 00 00 00       	push   0x5
    608b:	e9 90 ff ff ff       	jmp    6020 <_init+0x20>
  ```
- The PLT and the GOT are dynamic linker structures. The PLT (Procedure Linkage Table) contains indirect jumps (through the GOT) to dynamic functions, and fallback jumps to dl_runtime_resolve(). The GOT (Global Offset Table) contains the address of already resolved functions, or the instruction in the PLT following the indirect jump, so it can redirect to the fallback jump.
- For understanding linux system calls important files are:
  - `/include/linux/syscalls.h` (all the supported system calls in linux)
  - `/arch/arm/kernel/entry-common.S` (implementation of system call at register level)
  - `/arch/arm/kernel/calls.S` (system call numbers)
  - `/arch/arm/include/asm/unistd.h` (address of system call)
- Note: system call table can be addressed only from `system.map`.
- Look at kernel source code and documentation.
- https://blog.packagecloud.io/the-definitive-guide-to-linux-system-calls/
- GDB can catch syscalls with `catch syscall` or `catch syscall <syscall-number>`.
