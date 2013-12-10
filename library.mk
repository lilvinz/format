

FORMAT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CSRC += $(wildcard $(FORMAT_DIR)/src/format.c)
CSRC += $(wildcard $(FORMAT_DIR)/lib/*.c)
EXTRAINCDIRS += $(FORMAT_DIR)/src
EXTRAINCDIRS += $(FORMAT_DIR)/lib
