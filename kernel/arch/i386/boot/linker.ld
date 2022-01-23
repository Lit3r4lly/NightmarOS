ENTRY(start)
SECTIONS
{

  .text 0x100000 :
  {
    CodeStart = .; _CodeStart = .; __CodeStart = .;
    *(.multiboot)
    *(.text)
    . = ALIGN(4096);
  }
  CodeEnd = .; _CodeEnd = .; __CodeEnd = .;

  .data :
  {
     data = .; _data = .; __data = .;
     *(.data)
     *(.rodata)
     . = ALIGN(4096);
  }

  .bss :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    . = ALIGN(4096);
  }

  end = .; _end = .; __end = .;
}