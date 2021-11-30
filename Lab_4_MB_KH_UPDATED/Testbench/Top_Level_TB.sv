`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 11:58:19 PM
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
logic clk,f;
logic [7:0] in;
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
#0.55
f = 1;
in = 212;
#700
f = 0;
in = 50;
#700 f = 0; in = 1; // c to f
      #700 in = 8'b00000000;
      #700 in = 8'b00000001;
      #700 in = 8'b00000010;
      #700 in = 8'b01100100;
      #700 f = 1;      // f to c
      #700 in = 8'b00100000;
      #700 in = 8'b00100001;
      #700 in = 8'b00100010;
      #700 in = 8'b00100011;
      #700 in = 8'b11010100;
$stop;
end
endmodule
