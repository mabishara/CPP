# Asynchronous clocks
set_clock_groups -asynchronous -group [ get_clocks { CCC_0_0/CCC_0_0/pll_inst_0/OUT0 } ]
set_clock_groups -asynchronous -group [ get_clocks { DDR3_0_0/CCC_0/pll_inst_0/OUT1 } ]

#JTAG_tck_constraints
create_clock -name { TCK } \
-period 33.33 \
-waveform { 0 16.665 } \
[ get_ports { TCK } ]

#set_multicycle_path -setup_only 2 -from [ get_pins { DDR3_0_0/DDRPHY_BLK_0/IOD_TRAINING_0/COREDDR_TIP_INT_U/reset_n_int*/CLK } ] -to [ get_clocks { DDR3_0_0/CCC_0/pll_inst_0/OUT1 } ]

