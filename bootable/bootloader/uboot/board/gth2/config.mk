ifeq ($(TBASE),0)
TEXT_BASE = 0
else
ifeq ($(TBASE),1)
TEXT_BASE = 0xbfc10070
else
ifeq ($(TBASE),2)
TEXT_BASE = 0xbfc30070
else
## Only to make ordinary make work
TEXT_BASE = 0x90000000
endif
endif
endif
