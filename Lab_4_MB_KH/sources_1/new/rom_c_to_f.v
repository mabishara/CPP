`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 12:40:12 AM
// Design Name: 
// Module Name: rom_c_to_f
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


module rom_c_to_f(
  input logic clk,
  input logic [7:0] in,
  output logic [7:0] converted
  );
  
  (*rom_style = "block" *)logic [7:0] c_to_f [0:100];
   
  initial
  begin
      $readmemb("c_to_f.mem", c_to_f);
  end
  
  always_ff @(posedge clk)
  begin
    converted <= c_to_f[in];
  end
endmodule
