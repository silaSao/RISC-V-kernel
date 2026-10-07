build:
	riscv64-unknown-elf-as -march=rv64g -mabi=lp64d -o start.o start.s
	riscv64-unknown-elf-as -march=rv64g -mabi=lp64d -o switch_context.o switch_context.s
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -nostdlib -c kernel.c -o kernel.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -nostdlib -c io.c -o io.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -nostdlib -c str.c -o str.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -nostdlib -c allocator.c -o allocator.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -nostdlib -c process_handler.c -o process_handler.o
	riscv64-unknown-elf-ld -T link.ld -o kernel.elf start.o switch_context.o kernel.o io.o str.o allocator.o process_handler.o

run:
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -nographic

clean:
	rm -f start.o switch_context.o kernel.o io.o str.o allocator.o process_handler.o kernel.elf