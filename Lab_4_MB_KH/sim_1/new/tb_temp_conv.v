`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 10:07:38 PM
// Design Name: 
// Module Name: tb_temp_conv
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


module tb_temp_conv();
  logic clk;
  logic format;
  logic [7:0] in;
  logic [7:0] converted;
  
  localparam T = 10;
  
  top_temp_conv uut(.*);
//  rom_with_file uut(.*);
  
  //clk
  always
    begin
      clk = 1'b1;
      #(T/2);
      clk = 1'b0;
      #(T/2);
    end

  initial
    begin
      format = 0; in = 1; // c to f
      #(100*T) in = 8'b00000000;
      #(100*T) in = 8'b00000001;
      #(100*T) in = 8'b00000010;
      #(100*T) in = 8'b01100100;
      #(100*T) format = 1;      // f to c
      #(100*T) in = 8'b00100000;
      #(100*T) in = 8'b00100001;
      #(100*T) in = 8'b00100010;
      #(100*T) in = 8'b00100011;
      #(100*T) in = 8'b11010100;
    end
endmodule
