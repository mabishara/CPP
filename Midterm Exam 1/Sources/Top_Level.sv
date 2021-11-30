`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/26/2020 01:42:34 PM
// Design Name: 
// Module Name: Top_Level
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

//Top Level Desgin
module Top_Level(
input logic clk, en, reset,
input logic [7:0] in,
output logic [15:0] out,
output logic [7:0] E,
output logic [6:0] CA2G,
output logic dp
    );

logic max_tick;
logic [25:0] data;
Rom_LinearTransform lin(clk,in,data);
mod_m_counter delay(data,clk,reset,en,max_tick);
LRShifter lr(clk,en,reset,max_tick,out);
Main7SD seven_seg(clk, in, E, CA2G, dp);
endmodule
