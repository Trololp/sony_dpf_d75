ENTRY(_start)

SECTIONS
{
  . = 0x802A0000;

  .text : {
    _start = .;     /* Make sure _start is exactly here */
    *(.start*)      /* Place your startup code first */
    *(.text*)       /* Then all normal .text code */
  }

  .rodata : { *(.rodata*) }
  .data   : { *(.data*) }

  .bss : {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  }

  /DISCARD/ : {
    *(.comment)
    *(.note*)
  }
}

