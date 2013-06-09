onerror {resume}
quietly virtual signal -install /pmp_tb { (context /pmp_tb )(PIC_PB_CLK &PIC_ADDR &PIC_PMDIN )} GG
quietly WaveActivateNextPane {} 0
add wave -noupdate -expand -group FPGA_COMMON /pmp_tb/FPGA_CLK
add wave -noupdate -expand -group FPGA_COMMON /pmp_tb/RESET
add wave -noupdate -expand -group PIC /pmp_tb/PIC_PB_CLK
add wave -noupdate -expand -group PIC -radix hexadecimal /pmp_tb/PIC_ADDR
add wave -noupdate -expand -group PIC -radix hexadecimal /pmp_tb/PIC_PMDIN
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMALH
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMALL
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMCS2
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMD
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMRD
add wave -noupdate -group PMP /pmp_tb/PIC_PMP_PMWR
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_D
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_A
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_RD
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_WR
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_CS_RESET
add wave -noupdate -expand -group FPGA_BUS /pmp_tb/DUT/BUS_CS_LED
add wave -noupdate -group LED /pmp_tb/DUT/LED1
add wave -noupdate -group LED /pmp_tb/DUT/LED2
add wave -noupdate -group LED /pmp_tb/DUT/LED_interface/LED_register
add wave -noupdate -group RESET /pmp_tb/DUT/RESET_software/SOFT_RESET
add wave -noupdate -group RESET /pmp_tb/DUT/RESET_software/SOFT_RESET_N
add wave -noupdate -group RESET /pmp_tb/DUT/RESET_software/RESET_register
add wave -noupdate -group RESET /pmp_tb/DUT/HARD_SOFT_RESET
add wave -noupdate -group ENCODER_1 -expand -group Inputs /pmp_tb/DUT/ENCODER1_interface/ENCODER_R_channel_A
add wave -noupdate -group ENCODER_1 -expand -group Inputs /pmp_tb/DUT/ENCODER1_interface/ENCODER_R_channel_B
add wave -noupdate -group ENCODER_1 -expand -group Inputs /pmp_tb/DUT/ENCODER1_interface/ENCODER_L_channel_A
add wave -noupdate -group ENCODER_1 -expand -group Inputs /pmp_tb/DUT/ENCODER1_interface/ENCODER_L_channel_B
add wave -noupdate -group ENCODER_1 -expand -group Regs /pmp_tb/DUT/ENCODER1_interface/latch_reg
add wave -noupdate -group ENCODER_1 -expand -group Regs -radix hexadecimal /pmp_tb/DUT/ENCODER1_interface/counter_R_reg
add wave -noupdate -group ENCODER_1 -expand -group Regs -radix hexadecimal /pmp_tb/DUT/ENCODER1_interface/counter_L_reg
add wave -noupdate -group ENCODER_1 -expand -group Regs /pmp_tb/DUT/ENCODER1_interface/dummy_reg
add wave -noupdate -group ENCODER_1 /pmp_tb/DUT/ENCODER1_interface/reset_latch_reg
add wave -noupdate -group ENCODER_1 /pmp_tb/DUT/ENCODER1_interface/counter_latch_sync1
add wave -noupdate -group ENCODER_1 /pmp_tb/DUT/ENCODER1_interface/counter_latch_sync2
add wave -noupdate -group ENCODER_1 -radix hexadecimal /pmp_tb/DUT/ENCODER1_interface/counter_R/tmp
add wave -noupdate -group ENCODER_1 -radix hexadecimal /pmp_tb/DUT/ENCODER1_interface/counter_L/tmp
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/UART/BAUD_RATE
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/RxTx
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/BUS_CS
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/status_reg
add wave -noupdate -group AX12_1 -radix hexadecimal /pmp_tb/DUT/AX12_1_interface/input_reg
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/output_reg
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/dummy_reg
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/received_flag
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/UART/Int_DataReceived
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/UART/Int_DataSent
add wave -noupdate -group AX12_1 /pmp_tb/DUT/AX12_1_interface/send_flag
add wave -noupdate -group AX12_1 -expand -group TRANSMITTER /pmp_tb/DUT/AX12_1_interface/UART/Transmitter/current_state
add wave -noupdate -group AX12_1 -expand -group TRANSMITTER /pmp_tb/DUT/AX12_1_interface/UART/Transmitter/Tx
add wave -noupdate -group AX12_1 -expand -group TRANSMITTER /pmp_tb/DUT/AX12_1_interface/UART/Data_ToSend
add wave -noupdate -group AX12_1 -expand -group TRANSMITTER /pmp_tb/DUT/AX12_1_interface/UART/Transmitter/Tx
add wave -noupdate -group AX12_1 -expand -group RECEIVER /pmp_tb/DUT/AX12_1_interface/UART/Receiver/Rx
add wave -noupdate -group AX12_1 -expand -group RECEIVER /pmp_tb/DUT/AX12_1_interface/UART/Data_Received
add wave -noupdate -group AX12_1 -expand -group RECEIVER /pmp_tb/DUT/AX12_1_interface/UART/Receiver/buffer_received
add wave -noupdate -group AX12_1 -expand -group RECEIVER /pmp_tb/DUT/AX12_1_interface/UART/Receiver/Data_Received
add wave -noupdate -group AX12_1 -expand -group RECEIVER /pmp_tb/DUT/AX12_1_interface/UART/Receiver/current_state
add wave -noupdate -group COLOR_SENSOR_1 /pmp_tb/DUT/COLOR_SENSOR_1/IN_SIGNAL
add wave -noupdate -group COLOR_SENSOR_1 /pmp_tb/DUT/BUS_CS_COLOR_SENSOR_1
add wave -noupdate -group COLOR_SENSOR_1 /pmp_tb/DUT/COLOR_SENSOR_1/IN_SIGNAL_RISING_EDGE
add wave -noupdate -group COLOR_SENSOR_1 /pmp_tb/DUT/COLOR_SENSOR_1/IN_SIGNAL_FALLING_EDGE
add wave -noupdate -group COLOR_SENSOR_1 -radix hexadecimal /pmp_tb/DUT/COLOR_SENSOR_1/period_reg
add wave -noupdate -group COLOR_SENSOR_1 -radix unsigned -childformat {{/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(7) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(6) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(5) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(4) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(3) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(2) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(1) -radix unsigned} {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(0) -radix unsigned}} -subitemconfig {/pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(7) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(6) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(5) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(4) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(3) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(2) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(1) {-height 16 -radix unsigned} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter(0) {-height 16 -radix unsigned}} /pmp_tb/DUT/COLOR_SENSOR_1/half_period_counter
add wave -noupdate -group COLOR_CONTROL /pmp_tb/DUT/FPGA_SERVO_5
add wave -noupdate -group COLOR_CONTROL /pmp_tb/DUT/FPGA_SERVO_3
add wave -noupdate -group COLOR_CONTROL /pmp_tb/DUT/COLOR_CONTROL/GPIO_REG
add wave -noupdate -group BEACON /pmp_tb/DUT/BEACON_CONTROL/GPIO_REG
add wave -noupdate -group BEACON /pmp_tb/FPGA_GPIO_4
add wave -noupdate -group BEACON /pmp_tb/FPGA_GPIO_2
add wave -noupdate -group BEACON /pmp_tb/FPGA_GPIO_9
add wave -noupdate -group BEACON /pmp_tb/FPGA_GPIO_6
add wave -noupdate -group GPIO /pmp_tb/DUT/GPIOs/GPIO_REG
add wave -noupdate -group GPIO /pmp_tb/DUT/FPGA_GPIO_1
add wave -noupdate -group GPIO /pmp_tb/DUT/FPGA_GPIO_3
add wave -noupdate -group GPIO /pmp_tb/DUT/FPGA_GPIO_7
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/period_reg
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/BUS_CS_SERVO_0
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/current_state
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/next_state
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/period_counter
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/sig_counter
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/FPGA_SERVO_9
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/base_clk
add wave -noupdate -expand -group SERVO_0 /pmp_tb/DUT/SERVO_0/BC_edge
add wave -noupdate -expand -group SERVO_1 /pmp_tb/DUT/FPGA_SERVO_7
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {20872332 ns} 0}
configure wave -namecolwidth 241
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ns} {42420 us}
