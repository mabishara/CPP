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
    input logic [31:0] in,
    input logic [4:0] shift,
    output logic [31:0] y
    );
    logic [31:0] s0, s1, s2, s3;
    //stage 0, shift 0 or 1 bit
    assign s0 = shift[0] ? {in[30:0], in[31]} : in;
     //stage 1, shift 0 or 2 bits
    assign s1 = shift[1] ? {s0[29:0], s0[31:30]} : s0;
    //stage 2, shift 0 or 4 bits
    assign s2 = shift[2] ? {s1[27:0], s1[31:28]} : s1;
    //stage 3, shift 0 or 8 bits
    assign s3 = shift[3] ? {s2[23:0], s2[31:24]} : s2;
    //stage 4, shift 0 or 16 bits
    assign y = shift[4] ? {s2[15:0], s2[31:16]} : s3;            

endmodule
