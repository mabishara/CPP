`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/27/2020 03:05:09 AM
// Design Name: 
// Module Name: Rom_LinearTransform
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

//Block ROM inspired by Lab 4 - Temperature Conversion due to linear transformation
module Rom_LinearTransform(
input logic clk,
input logic [7:0] addr,
output logic [25:0] data
    );
    (*rom_style = "block" *)logic [25:0] rom [0:255];
    initial
        $readmemb("LinearTransform.mem", rom);
        always_ff @(posedge clk)
        data <= rom[addr];
endmodule
