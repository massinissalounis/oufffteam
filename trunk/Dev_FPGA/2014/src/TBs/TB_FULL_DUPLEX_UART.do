onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_full_duplex_uart/FPGA_CLK
add wave -noupdate /tb_full_duplex_uart/RESET
add wave -noupdate /tb_full_duplex_uart/Rx
add wave -noupdate /tb_full_duplex_uart/Int_DataReceived
add wave -noupdate /tb_full_duplex_uart/Data_Received
add wave -noupdate /tb_full_duplex_uart/Data_ToSend
add wave -noupdate /tb_full_duplex_uart/UUT/BAUD_RATE
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/UUT/Transmitter/current_state
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/UUT/Transmitter/next_state
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/Tx
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/Int_DataSent
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/Send
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/UUT/Transmitter/BR_edge
add wave -noupdate -expand -group TRANSMITTER /tb_full_duplex_uart/UUT/Transmitter/counter_data
add wave -noupdate /tb_full_duplex_uart/UUT/Transmitter/clock_UART_old
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {8620 ns} 0}
configure wave -namecolwidth 266
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
WaveRestoreZoom {0 ns} {19176 ns}
