#
# Makefile
#-L/home/gec/freetype-2.12.1/tmp/lib -I/home/gec/freetype-2.12.1/tmp/include/freetype2
CC = arm-linux-gcc
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -O3 -g0   -I$(LVGL_DIR)/ -I$(LVGL_DIR)/usrCode -std=gnu99
LDFLAGS ?= -lm 
BIN = demo


#Collect the files to compile
USRCODESRC = ${shell find $(LVGL_DIR)/usrCode -name '*.c'}
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

# CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))
USRCODEOBJ=$(USRCODESRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC) $(USRCODESRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES


all: default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
# @echo "CC $<"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ) $(USRCODEOBJ)
	@$(CC) -o $(BIN) $(AOBJS) $(COBJS) $(USRCODEOBJ) $(LDFLAGS) $(MAINOBJ)

clean: 
	rm -f ${BIN} $(AOBJS) $(COBJS) $(MAINOBJ) $(USRCODEOBJ)

send:
	scp -O demo root@192.168.172.115:/root
