
# internal flash
BL_ORIGIN           := 0x08000000 # @    0 KiB
BL_SIZE             := 0x00008000 #     32 KiB (8 sectors of  4 KiB)
EE_ORIGIN           := 0x08008000 # @   32 KiB
EE_SIZE             := 0x00000000 #     0 KiB (0 sectors of  4 KiB)
# 1 sector of 64 KiB is unused
FW_ORIGIN           := 0x08008000 # @  32 KiB
FW_SIZE             := 0x00018000 #    96 KiB (24 sectors of 4 KiB)
# note: the remaining space is being unused for now
EF_ORIGIN           := 0x08000000 # @    0 KiB
EF_SIZE             := 0x00020000 #    128 KiB

OPENOCD_JTAG_CONFIG := stlink-v2.cfg
OPENOCD_TRANSPORT   := hla_swd
OPENOCD_CONFIG      := stm32f0x.cfg
