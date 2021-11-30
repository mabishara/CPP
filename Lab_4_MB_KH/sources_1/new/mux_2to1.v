`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 12:06:34 AM
// Design Name: 
// Module Name: mux_2to1
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


module mux_2to1(
    input logic [7:0] x0,
    input logic [7:0] x1,
    input logic select,
    output logic [7:0] y
  );
  
  always_comb
    begin
      case(select)
        1'b0: y=x0;
        1'b1: y=x1;
        default y=x0;
      endcase
    end
endmodule
