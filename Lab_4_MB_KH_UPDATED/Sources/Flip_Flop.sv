`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 11:08:57 PM
// Design Name: 
// Module Name: Flip_Flop
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


module Flip_Flop(
input logic clk, f,
input logic [7:0] in,
output logic [7:0] addr
    );
always_ff @(posedge clk)
begin
if (f)
     addr <= in - 32;
else
     addr <= in;
end
endmodule
