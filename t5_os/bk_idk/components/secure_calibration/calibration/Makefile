ifndef TOOLCHAIN_PATH

#ARM GNU gcc v10.3-2021 has the bug to
#resolve link option -nostartfiles, prefer v10-2020-q4
#TOOLCHAIN_PATH := /opt/gcc-arm-none-eabi-10.3-2021.10/bin

# Comments from TF-M official doc:
# GNU Arm compiler version 10-2020-q4-major has an issue in CMSE support.
# Select other GNU Arm compiler versions instead
#TOOLCHAIN_PATH := /opt/gcc-arm-none-eabi-10-2020-q4-major/bin

TOOLCHAIN_PATH := /opt/gcc-arm-none-eabi-9-2020-q2-update/bin
endif

# Default goal is build all images
.DEFAULT_GOAL			:= all

################################################################################
# Get the dir of codebase, requires make version 3.81 or later
################################################################################

top-dir := $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))..))
mk-dir	:= $(abspath ./build/mk)

################################################################################
# Default values for build configurations
################################################################################

COMPONENT_OUT := ubl
include ${mk-dir}/config.mk
include ${mk-dir}/build_macros.mk

# Common variables
ifeq ($(BOOT_V2), Y)
BOOT_TOP                       :=  ./boot/boot_v2
else
BOOT_TOP                       :=  ./boot/boot_v1
endif

UT_TOP                         :=  ./utils/ce_lite/examples

MBEDTLS                        :=./utils/ce_lite/port_mbedtls/mbedtls
MBEDTLS_PORT                   :=./utils/ce_lite/port_mbedtls/mbedtls_port
MBEDTLS_ALT                    :=./utils/ce_lite/port_mbedtls/bk_mbedtls_alt

FIH_TOP                        :=  ./fih

BOOTROM_BIN                    := $(OUT_DIR)/bootrom/bootrom.bin
BOOTROM_BIN_OUT                := ${top-dir}/out
EXT_IMG_BIN                    := $(OUT_DIR)/ext_img/ext_img.bin
EXT_IMG_BIN_OUT                := ${top-dir}/out

################################################################################
# Toolchain
################################################################################

ASFLAGS			+= 	${DEFINES} ${INCLUDES}
CFLAGS			+= 	${DEFINES} ${INCLUDES}

################################################################################
# Common sources and include directories
################################################################################

include common.mk

################################################################################
# Generic definitions
################################################################################

PLATFORM_ROOT := hal
include ${mk-dir}/plat_helpers.mk

################################################################################
# Include the platform specific Makefile(the platform
# makefile may use all previous definitions in this file)
################################################################################

include ${PLAT_MAKEFILE_FULL}

################################################################################
# Include the arch specific Makefile
################################################################################

include arch/arch.mk

################################################################################
# Build options checks
################################################################################

$(eval $(call assert_boolean,CONFG_DEBUG))

################################################################################
# Add definitions to the cpp preprocessor based on the current build options.
# This is done after including the platform specific makefile to allow the
# platform to overwrite the default options
################################################################################

$(eval $(call add_define,PLAT_$(call uppercase,${PLAT})))
$(eval $(call add_define,CONFIG_$(call uppercase,${PLAT})))
$(eval $(call add_define,LOG_LEVEL))

################################################################################
# Include specific makefiles
################################################################################

ifeq ($(BOOT_V2), Y)
include boot/boot_v2/boot.mk
else
include boot/boot_v1/boot.mk
endif

ifeq ($(TE200_UT), Y)
#include utils/ce_lite/examples/ut.mk
else 
include utils/ce_lite/port_mbedtls/mbedtls.mk
endif

#include fih/fih.mk

include bootrom.mk
#include ext_img.mk
-include user_define.mk

################################################################################
# Build targets
################################################################################

.PHONY:	all msg_start clean realclean distclean help
.SUFFIXES:

all: msg_start

msg_start:
	@echo "Building ${PLAT}"

post_build:
	-${Q}cp -f $(BOOTROM_BIN) $(BOOTROM_BIN_OUT)

ext_post_build:
	-${Q}cp -f $(EXT_IMG_BIN) $(EXT_IMG_BIN_OUT)

clean:
	@echo "  CLEAN   $(OUT_DIR)/bootrom $(OUT_DIR)/ext_img"
	${Q}rm -f ${CLEANFILES}
	${Q}rm -fr $(OUT_DIR)/bootrom
	${Q}rm -fr $(OUT_DIR)/ext_img

realclean distclean:
	@echo "  REALCLEAN"
	${Q}rm -f ${CLEANFILES}
	${Q}rm -fr $(O)

help:
	@echo "usage: ${MAKE} [OPTIONS] [TARGET]"
	@echo ""
	@echo "CROSS_COMPILE is used to specify which compiler you wish to use."
	@echo "If no compiler is specified, CROSS_COMPILE defaults to: ${DFT_CROSS_COMPILE}"
	@echo ""
	@echo "Supported Options:"
	@echo "DEBUG=1: debug version"
	@echo "V=1: verbose build"
	@echo "clean: clean build"
	@echo "Please refer to the User Guide for a list of all supported options."
	@echo "Note that the build system doesn't track dependencies for build"
	@echo "options. Therefore, if any of the build options are changed"
	@echo "from a previous build, a clean build must be performed."
	@echo ""
	@echo "Supported Targets:"
	@echo "  all                     Build all individual binaries"
	@echo "  bootrom                 Build the BootROM binary"
	@echo "  clean                   Clean the build for the selected platform"
	@echo "  distclean               Remove all build artifacts for all platforms"
	@echo ""
	@echo "Note: most build targets require PLAT to be set to a specific platform."
	@echo ""
	@echo "example: "
	@echo "  CROSS_COMPILE=arm-none-eabi- make "
