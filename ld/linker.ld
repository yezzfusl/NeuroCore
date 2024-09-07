ENTRY(_start)

SECTIONS
{
    . = 0x10000;

    .text : {
        *(.text.start)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    .stack (NOLOAD) : {
        . = ALIGN(16);
        stack_bottom = .;
        . = . + 0x1000; /* 4KB of stack space */
        stack_top = .;
    }
}

