
################################################################################
## Project Settings
TARGET = modem
# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = 0
# MCU name, submodel and board
# - MCU used for compiler-option (-mcpu)
# - SUBMDL used for linker-script name (-T) and passed as define
# - BOARD just passed as define (optional)
MCU         = cortex-m3
CHIP        = STM32F10x_256k_48k
CPUFAMILY   = STM32F10X_MD
BOARD       = modem
F_XTAL      = 16000000
SYSCLOCK_CL = SYSCLK_FREQ_72MHz=72000000
## Output format. (can be ihex or binary or both)
LOADFORMAT = both
################################################################################
## Used Pathes
STMLIBDIR = ../common/lib.stm32
## Path to Linker-Scripts
LINKERSCRIPTPATH = $(STMLIBDIR)
LINKERSCRIPTINC  = $(STMLIBDIR)
##Librarys
STMSPDDIR = $(STMLIBDIR)/STM32F10x_StdPeriph_Driver
STMSPDSRCDIR = $(STMSPDDIR)/src
STMSPDINCDIR = $(STMSPDDIR)/inc
STMSUSBDIR = $(STMLIBDIR)/STM32_USB-FS-Device_Driver
STMUSBSRCDIR = $(STMSUSBDIR)/src
STMUSBINCDIR = $(STMSUSBDIR)/inc
CMSISDIR  = $(STMLIBDIR)/CMSIS/Core/CM3
FATSDDIR  = $(STMLIBDIR)/fat_sd
# RTOS DIRS
RTOS_SRC_DIR = ../common/rtos
RTOS_PORT_DIR = $(RTOS_SRC_DIR)/portable/GCC/ARM_CM3
RTOS_PORTPER_DIR = $(RTOS_PORT_DIR)/perepherial
RTOS_MEM_DIR =  $(RTOS_SRC_DIR)/portable/MemMang
################################################################################
# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
## CMSIS for STM32
SRC += $(CMSISDIR)/core_cm3.c
#SRC += $(CMSISDIR)/system_stm32f10x.c
## compiler-specific sources
SRC += $(STMLIBDIR)/startup_stm32f10x_md_mthomas.c
SRC += $(STMLIBDIR)/syscalls.c 
SRC += $(STMLIBDIR)/hwinit.c 

## RTOS
SRC	+= $(RTOS_SRC_DIR)/tasks.c 
SRC	+= $(RTOS_SRC_DIR)/queue.c 
SRC	+= $(RTOS_SRC_DIR)/list.c 
SRC	+= $(RTOS_PORT_DIR)/port.c 
SRC	+= $(RTOS_MEM_DIR)/heap_2.c 
## used parts of the STM-Library
SRC += $(STMSPDSRCDIR)/stm32f10x_adc.c
SRC += $(STMSPDSRCDIR)/stm32f10x_usart.c
SRC += $(STMSPDSRCDIR)/stm32f10x_flash.c
SRC += $(STMSPDSRCDIR)/stm32f10x_gpio.c
SRC += $(STMSPDSRCDIR)/stm32f10x_rcc.c
SRC += $(STMSPDSRCDIR)/stm32f10x_spi.c
SRC += $(STMSPDSRCDIR)/stm32f10x_rtc.c
SRC += $(STMSPDSRCDIR)/stm32f10x_bkp.c
SRC += $(STMSPDSRCDIR)/stm32f10x_pwr.c
SRC += $(STMSPDSRCDIR)/stm32f10x_dma.c
SRC += $(STMSPDSRCDIR)/stm32f10x_tim.c
SRC += $(STMSPDSRCDIR)/misc.c
## perepherial library source
SRC += $(STMLIBDIR)/adc.c
SRC += $(STMLIBDIR)/uart.c

## Main Application
SRC += main.c 
SRC += ./tasks/logica.c
SRC += ./tasks/rs485.c
#usb support
#SRC += ./usb/usb_desc.c
#SRC += ./usb/usb_endp.c
#SRC += ./usb/usb_istr.c
#SRC += ./usb/usb_prop.c
#SRC += ./usb/usb_pwr.c
#USB FS LIBRARY
#SRC += $(STMUSBSRCDIR)/usb_core.c
#SRC += $(STMUSBSRCDIR)/usb_init.c
#SRC += $(STMUSBSRCDIR)/usb_int.c
#SRC += $(STMUSBSRCDIR)/usb_mem.c
#SRC += $(STMUSBSRCDIR)/usb_regs.c
#SRC += $(STMUSBSRCDIR)/usb_sil.c


# List C source files here which must be compiled in ARM-Mode (no -mthumb).
# use file-extension c for "c-only"-files
SRCARM = 

# List C++ source files here.
# use file-extension .cpp for C++-files (not .C)
CPPSRC = 

# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension .cpp for C++-files (not .C)
#CPPSRCARM = $(TARGET).cpp
CPPSRCARM = 

# List Assembler source files here.
# Make them always end in a capital .S. Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = 

# List Assembler source files here which must be assembled in ARM-Mode..
ASRCARM  =

################################################################################
# List any extra directories to look for include files here.
#    Each directory must be seperated by a space.
EXTRAINCDIRS  = $(STMSPDINCDIR) $(STMUSBINCDIR) $(CMSISDIR) 
EXTRAINCDIRS += $(FATSDDIR) $(MININIDIR) $(STMEEEMULINCDIR)
EXTRAINCDIRS += $(STMLIBDIR) $(SWIMSRCDIR)
# RTOS
EXTRAINCDIRS += $(RTOS_SRC_DIR)/include
EXTRAINCDIRS += $(RTOS_PORT_DIR)
# Main App
EXTRAINCDIRS  += ./src 
EXTRAINCDIRS  += ./tasks 
################################################################################
# Extra libraries
#    Each library-name must be seperated by a space.
#    i.e. to link with libxyz.a, libabc.a and libefsl.a: 
#    EXTRA_LIBS = xyz abc efsl
# for newlib-lpc (file: libnewlibc-lpc.a):
#    EXTRA_LIBS = newlib-lpc
EXTRA_LIBS =

# List any extra directories to look for library files here.
# Also add directories where the linker should search for
# includes from linker-script to the list
#     Each directory must be seperated by a space.
EXTRA_LIBDIRS = $(LINKERSCRIPTINC)


include ../common/build/Makefile.cortex-m3

