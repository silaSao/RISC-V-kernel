.PHONY: build
build:
	riscv64-unknown-elf-as -march=rv64g -mabi=lp64d -o build/start.o start.s
	riscv64-unknown-elf-as -march=rv64g -mabi=lp64d -o build/switch_context.o switch_context.s
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c kernel.c -o build/kernel.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c io.c -o build/io.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c str.c -o build/str.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c allocator.c -o build/allocator.o
	riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c process_handler.c -o build/process_handler.o
	cd build && riscv64-unknown-elf-ld -T ../link.ld -o kernel.elf start.o switch_context.o kernel.o io.o str.o allocator.o process_handler.o

build_debug:
	riscv64-unknown-elf-as -g -march=rv64g -mabi=lp64d -o build/start.o start.s
	riscv64-unknown-elf-as -g -march=rv64g -mabi=lp64d -o build/switch_context.o switch_context.s
	riscv64-unknown-elf-gcc -g -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c kernel.c -o build/kernel.o
	riscv64-unknown-elf-gcc -g -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c io.c -o build/io.o
	riscv64-unknown-elf-gcc -g -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c str.c -o build/str.o
	riscv64-unknown-elf-gcc -g -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c allocator.c -o build/allocator.o
	riscv64-unknown-elf-gcc -g -march=rv64g -mabi=lp64d -mcmodel=medany -ffreestanding -c process_handler.c -o build/process_handler.o
	cd build && riscv64-unknown-elf-ld -T ../link.ld -o kernel.elf start.o switch_context.o kernel.o io.o str.o allocator.o process_handler.o

run:
	cd build && qemu-system-riscv64 -machine virt -bios none -nographic -kernel kernel.elf 

run_debug:
	cd build && qemu-system-riscv64 -machine virt -bios none -nographic -kernel kernel.elf -S -gdb tcp::1234

clean:
	cd build && rm -f start.o switch_context.o kernel.o io.o str.o allocator.o process_handler.o kernel.elf