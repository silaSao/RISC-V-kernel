.section .text
.global _start

_start:
    la sp, stack_top

    call kernel_main
    
done:
    j done

.section .bss
.align 16
stack_bottom:
    .space 4096
stack_top:
