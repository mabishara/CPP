`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 04:26:59 AM
// Design Name: 
// Module Name: Main7SD
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

//**MODELED AFTER ECE3300 VERILOG CODE AND TRANSLATED TO SYSTEMVERLIOG**
module Main7SD(
input logic clk,
input logic [7:0] binary,
output logic [7:0] E,
output logic [6:0] CA2G,
output logic dp
    );
logic [11:0] BCD;
logic [1:0] WADD;
logic [5:0] DIN;
logic W;
B2BCD bintodec(clk,binary,BCD);
DisplayController disp(clk, BCD, WADD, DIN, W);
System sys(DIN, WADD, W, clk, E, CA2G, dp);
endmodule
