X86EMU =  -I../bios_emulator/scitech/include -I../bios_emulator/scitech/src/x86emu

TEXT_BASE = 0xfff00000

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -Wa,-mregnames -DEASTEREGG $(X86EMU) -Dprintk=printf #-DDEBUG
