SECTIONS {
    . = 0x80000000;
    .text : {*start.o(.text*) *(.text)}
    .data : {*(.data)}
    .rodata : {*(.rodata)}
    .bss : {*(.bss)}
    
}
