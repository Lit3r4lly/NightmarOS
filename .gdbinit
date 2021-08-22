target remote localhost:1234
symbol-file NightmareOS.sym
set disassembly-flavor intel
break *kernel_main
continue