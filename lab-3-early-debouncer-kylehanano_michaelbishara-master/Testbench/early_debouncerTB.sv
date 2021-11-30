`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/14/2020 11:32:22 PM
// Design Name: 
// Module Name: early_debouncerTB
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module early_debouncerTB();
logic sw, reset, clk, db;
localparam T = 10;

early_debouncer uut(.*);
//clk
always
begin
clk = 1'b1;
#(T/2);
clk = 1'b0;
#(T/2);
end

initial
begin
reset = 1'b1;
#5000000
reset = 1'b0;
end
initial
begin
#1000000
sw = 0;
#5000000
sw = 1;
#7500000
sw = 0;
#7500000
sw = 1;
#2500000
sw = 0;
#5000000
sw = 1;
#10500000
sw = 0;
#5000000
sw = 1;
#5000000
sw = 0;
#30000000
sw = 1;
#40000000
sw = 0;
#10000000
$stop;
end
endmodule
