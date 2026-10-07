.section .text
.global _start

_start:
    # Set up stack
    la sp, stack_top
    
    # Jump to C code
    call kernel_main
    
    # Hang if kernel returns
done:
    j done

# Stack (grows downward)
.section .bss
.align 16
stack_bottom:
    .space 4096
stack_top:
