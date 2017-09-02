
# add board to target lists
BL_BOARDS += blinky
FW_BOARDS += blinky
EF_BOARDS += blinky
FT_BOARDS += blinky
SIM_BOARDS += blinky

# add dependencies for top level makefile
ef_blinky_all: fw_blinky_all bl_blinky_all
fw_blinky_all: bl_blinky_all
ft_blinky_all: ef_blinky_all

fw_blinky_program: fw_blinky_all
bl_blinky_program: bl_blinky_all
ef_blinky_program: ef_blinky_all
