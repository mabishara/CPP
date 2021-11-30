`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/26/2020 04:51:16 PM
// Design Name: 
// Module Name: Top_Level_TB
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


module Top_Level_TB();
localparam T = 10;
logic clk,en,reset;
logic [7:0] in;
logic [15:0] out;
logic [7:0] E;
logic [6:0] CA2G;
logic dp;
Top_Level uut(.*);
always
    begin
      clk = 1'b1;
      #(T/2);
      clk = 1'b0;
      #(T/2);
    end
initial begin
en = 1;
in = 0;
reset = 1;
#100
reset = 0;
#100

$stop;
end
endmodule