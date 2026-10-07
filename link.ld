SECTIONS {
    . = 0x80000000;      /* Start address */
    .text : {*(.text)}
    .rodata : {*(.rodata)}
    .bss : {*(.bss)}
    .data : {*(.data)}
}
