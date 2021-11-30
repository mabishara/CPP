`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2020 12:06:20 AM
// Design Name: 
// Module Name: SquareWave_TB
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


module SquareWave_TB();
//declaration
localparam N = 4;
localparam T = 10;
logic clk, reset;
logic [N-1:0] m,n;
logic q;

//uut
SquareWave #(.N(N))uut(.*);

//clk
always
begin
clk = 1'b1;
#(T/2);
clk = 1'b0;
#(T/2);
end

//inital reset
initial
begin
reset = 1'b1;
#100
reset = 1'b0;
end

//test vectors
initial
begin
m = 4'b0001;
n = 4'b0001;
#900
m = 4'b0011;
n = 4'b0010;
#2000
m = 4'b1101;
n = 4'b1000;
#3000
$stop;
end

endmodule
