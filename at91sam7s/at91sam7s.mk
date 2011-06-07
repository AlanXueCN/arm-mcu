# Processor dependent make definitions

# $Id$

CPU		= arm7tdmi
CPUFLAGS	=
TEXTBASE	?= 0x00000000

AT91LIB		= $(MCUDIR)/at91lib

CFLAGS		+= -I$(AT91LIB)
LDFLAGS		+= -Wl,--section-start=startup=$(TEXTBASE)

LIBOBJS		= cpu.o device.o serial.o syscalls.o

.PHONY:		clean_$(MCU) reallyclean_$(MCU) distclean_$(MCU) lib reset

.SUFFIXES:	.flashocd

# Build processor dependent support library

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	for F in $(AT91LIB)/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(AR) crs lib$(MCU).a $(AT91LIB)/*.o

lib: lib$(MCU).a

# Reset the target with OpenOCD

reset:
	$(OPENOCDRESET) $(OPENOCD) $(OPENOCDCFG)

# Define a suffix rule for programming the flash with OpenOCD

.bin.flashocd:
	$(OPENOCDFLASH) $(OPENOCD) $(OPENOCDCFG) $<

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
