

include $(dir $(lastword $(MAKEFILE_LIST)))/library.mk

CFLAGS += -DFORMAT_INCLUDE_FLOAT
