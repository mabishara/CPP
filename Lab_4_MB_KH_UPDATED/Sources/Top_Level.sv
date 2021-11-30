`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 11:05:43 PM
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


module Top_Level(
input logic clk, f,
input logic [7:0] in,
output logic [7:0] E,
output logic [6:0] CA2G,
output logic dp
    );
logic [7:0] addr, in_far, in_cel, data;
Flip_Flop ff(clk,f,in,addr);
Rom_Far far(clk,addr,in_far);
Rom_Cel cel(clk,addr,in_cel);
Rom_Picker_Mux mux(clk,f,in_far,in_cel,data);
Main7SD seven_seg(clk,data,E,CA2G,dp);
endmodule
