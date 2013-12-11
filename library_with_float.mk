

include $(dir $(lastword $(MAKEFILE_LIST)))/library.mk

CDEFS += -DFORMAT_INCLUDE_FLOAT
