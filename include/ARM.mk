# Generic Makefile for compiling ARM microcontroller firmware

# $Id$

ARMTOOLS	?= /usr/local/arm-tools
CROSS_COMPILE	?= $(ARMTOOLS)/bin/arm-elf-

CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
GDB		= $(CROSS_COMPILE)gdb

JLINKEXE	?= JLinkExe
JLINKSCRIPT	= jlinkscript.tmp
JLINKMCU	= $(MCU)
JLINKADDR	= 0x00000000

LPC21ISP	?= lpc21isp

OPENOCD		?= openocd
OPENOCDCFG	?= $(MCUDIR)/$(MCU).openocd
OPENOCDDEBUG	?= $(MCUDIR)/$(MCU).debugocd
OPENOCDFLASH	?= $(MCUDIR)/$(MCU).flashocd

MCUDIR		?= $(ARMSRC)/$(MCUFAMILY)
STARTUP		?= $(MCUDIR)/$(MCU).o
LINKERSCRIPT	?= $(MCUDIR)/$(MCU).ld
DEBUGSCRIPT	?= $(OPENOCDDEBUG)

CPUFLAGS	?=
CONFIGFLAGS	?=
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
IOFLAGS		?= -DINTEGER_STDIO
CFLAGS		+= -Wall -mcpu=$(CPU) $(CPUFLAGS) -D$(MCU) -D$(BOARDNAME)
CFLAGS		+= -I$(ARMSRC)/include -I$(MCUDIR)
CFLAGS		+= $(CONFIGFLAGS) $(DEBUGFLAGS) $(OPTFLAGS) $(IOFLAGS) $(DEBUG) $(EXTRAFLAGS)
LDFLAGS		+= -nostartfiles -T$(LINKERSCRIPT) -L$(MCUDIR) -l$(MCU) -Wl,-Map=$*.map,--cref $(EXTRAOBJS)

#GDBGUI		?= ddd --gdb --debugger
#GDBFLAGS	?= -tui

# Define default target placeholder

default_catch:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# These targets are not files

.PHONY: default_catch update clean startocd stopocd

# These are the target suffixes

.SUFFIXES: .asm .bin .debug .elf .flashjlink .flashocd .hex .o

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o.elf:
	cd $(MCUDIR) && $(MAKE) $(MCU).o lib$(MCU).a
	$(CC) $(CFLAGS) -o $@ $(STARTUP) $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.debug:
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(DEBUGSCRIPT) $<

.elf.hex:
	$(OBJCOPY) -S -O ihex --gap-fill=0 $< $@

.s.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

# Define a suffix rule for programming the flash with J-Link Commander

.bin.flashjlink:
	@echo "exec device=$(JLINKMCU)"			>$(JLINKSCRIPT)
	@echo "h"					>>$(JLINKSCRIPT)
	@echo "loadbin $<, 0x`dc -e '16o 16i $(subst 0x,,$(JLINKADDR)) $(subst 0x,,$(TEXTBASE)) + p'`"	>>$(JLINKSCRIPT)
	@echo "r"					>>$(JLINKSCRIPT)
	@echo "g"					>>$(JLINKSCRIPT)
	@echo "exit"					>>$(JLINKSCRIPT)
	-$(JLINKEXE) $(JLINKSCRIPT)
	@rm $(JLINKSCRIPT)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(OPENOCDFLASH) $(OPENOCD) $(OPENOCDCFG) $< $(TEXTBASE)

# Start and stop OpenOCD

startocd:
	$(OPENOCD) -f $(OPENOCDCFG) >openocd.log 2>&1 &

stopocd:
	killall openocd

# Update from source code repository

update:
	svn status
	svn update

# Clean out working files

clean:
	cd $(MCUDIR) && $(MAKE) clean_$(MCU)
	find * -name '*.o' -exec rm {} ";"
	rm -f *.a *.asm *.bin *.elf *.hex *.log *.map *.tmp Default.ini

reallyclean: clean
	cd $(MCUDIR) && $(MAKE) reallyclean_$(MCU)

distclean: reallyclean
	cd $(MCUDIR) && $(MAKE) distclean_$(MCU)

# Include MCU dependent makefile

include $(MCUDIR)/$(MCU).mk
