`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 12:40:31 AM
// Design Name: 
// Module Name: rom_f_to_c
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


module rom_f_to_c(

  input logic clk,
  input logic [7:0] in,
  output logic [7:0] converted
  );
  
  (*rom_style = "block" *)logic [7:0] f_to_c [0:180];
  
  initial
  begin
      $readmemb("f_to_c.mem", f_to_c);
  end
  
  always_ff @(posedge clk)
  begin
    converted <= f_to_c[in];
  end
endmodule