%.bin: %.elf
	riscv64-unknown-linux-gnu-objcopy -O binary $< $@
	xxd $@

%.elf: %.o
	riscv64-unknown-linux-gnu-ld -march=rv32i -m elf32lriscv_ilp32 -o $@ $<
	riscv64-unknown-elf-objdump -D $@

%.o: %.asm
	riscv64-unknown-linux-gnu-as -march=rv32i -mabi=ilp32 -o $@ $<
