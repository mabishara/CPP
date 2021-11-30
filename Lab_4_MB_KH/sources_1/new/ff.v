`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 12:27:20 AM
// Design Name: 
// Module Name: ff
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


module ff(
  input logic clk,
  input logic format,
  input logic [7:0] in,
  output logic [7:0] addr
  );
  
  always_ff @(posedge clk)
  begin
    if (format)
      addr <= (in - 8'b00100000);
    else
      addr <= in;
  end
  
endmodule
