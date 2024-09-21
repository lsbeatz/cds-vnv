# Verbose option (0: quiet(default), 1: print all)
V ?= 0
ifeq ($(V), 0)
Q := @
else
Q :=
endif

TEST_SUITE ?= queue
TARGET     ?= cds-$(TEST_SUITE)

ROOT_PATH  := $(shell pwd)
LIB_PATH   := $(ROOT_PATH)/lib
CORE_PATH  := $(ROOT_PATH)/core
TESTS_PATH := $(ROOT_PATH)/tests
BUILD_PATH := $(ROOT_PATH)/build/$(TEST_SUITE)

CC      := gcc
LD      := ld
OBJDUMP := objdump

CFLAGS   := -g -Wall
LDFLAGS  :=
LDLIBS   :=
MACROS   :=

INCLUDES := -I$(ROOT_PATH)/include

-include $(LIB_PATH)/build.mk
-include $(CORE_PATH)/build.mk
-include $(TESTS_PATH)/build.mk

SRCS := $(lib-srcs)
SRCS += $(core-srcs)
SRCS += $(tests-srcs)
OBJS := $(addprefix $(BUILD_PATH)/,$(SRCS:$(ROOT_PATH)/%.c=%.o))
ELF  := $(BUILD_PATH)/$(TARGET).elf
DASM := $(BUILD_PATH)/$(TARGET).dasm

MKDIRS := $(dir $(OBJS))

all: clean dir $(ELF) $(DASM) run

dir:
	$(Q) mkdir -p $(MKDIRS)

$(DASM) : $(ELF)
	$(Q) $(OBJDUMP) -D $(ELF) > $@

$(ELF): $(OBJS)
	$(Q) $(CC) $(LDFLAGS) $(MACROS) $(INCLUDES) $(OBJS) -o $@ $(LDLIBS)

$(BUILD_PATH)/%.o: %.c
	$(Q) $(CC) $(CFLAGS) $(MACROS) $(INCLUDES) -c $< -o $@

run:
	$(Q) $(ELF)

clean:
	$(Q) rm -rf $(BUILD_PATH)

tags:
	$(Q) ctags -R
