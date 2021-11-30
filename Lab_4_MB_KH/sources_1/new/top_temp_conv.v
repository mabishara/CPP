`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 12:07:25 AM
// Design Name: 
// Module Name: top_temp_conv
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


module top_temp_conv(
    input logic clk,
    input logic format,
    input logic [7:0] in,
    output logic [7:0] converted
    );
    
    logic [7:0] address, data1, data2;
    
    ff flip(clk, format, in, address);
    rom_c_to_f c_to_f(clk, address, data1);
    rom_f_to_c f_to_c(clk, address, data2);
    
    // format = 0 for c->f, format = 1 for f->c
    mux_2to1 mux(data1, data2, format, converted);
    
endmodule