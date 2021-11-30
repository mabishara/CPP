`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/01/2020 09:55:35 PM
// Design Name: 
// Module Name: LeftShifter
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


module LeftShifter(
    input logic [7:0] in,
    input logic [2:0] shift,
    output logic [7:0] y
    );
    logic [7:0] s0, s1;
    //stage 0, shift 0 or 1 bit
    assign s0 = shift[0] ? {in[6:0], in[7]} : in;
     //stage 1, shift 0 or 2 bits
    assign s1 = shift[1] ? {s0[5:0], s0[7:6]} : s0;
    //stage 2, shift 0 or 4 bits
    assign y = shift[2] ? {s1[3:0], s1[7:4]} : s1; 

endmodule
