ifeq ($(TBASE),0)
TEXT_BASE = 0
else
ifeq ($(TBASE),1)
TEXT_BASE = 0x80010070
else
ifeq ($(TBASE),2)
TEXT_BASE = 0x80030070
else
## Only to make ordinary make work
TEXT_BASE = 0x90000000
endif
endif
endif

OBJCFLAGS =	--set-section-flags=.ppcenv=contents,alloc,load,data
