
# add board to target lists
FW_BOARDS += blinky
FT_BOARDS += blinky
SIM_BOARDS += blinky

# add dependencies for top level makefile
fw_blinky_all:

fw_blinky_program: fw_blinky_all
