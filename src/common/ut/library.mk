

COMMON_UT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CSRC += $(wildcard $(COMMON_UT_DIR)/*.c)
EXTRAINCDIRS += $(COMMON_UT_DIR)

EXTRAINCDIRS += $(COMMON_UT_DIR)/..
