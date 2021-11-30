`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/01/2020 11:32:15 PM
// Design Name: 
// Module Name: PreAndPostReverse
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


module PreAndPostReverse(
    input logic [7:0] in,
    input logic [2:0] amount,
    input logic select,
    output logic [7:0] revout
    );
    logic [7:0] w0, w1, revin, revw1;
    generate
    genvar i;
    for (i = 0; i < 8; i++)
    assign revin[i] = in[7-i];
    endgenerate
    assign w0 = select ? in : revin;
    RightShifter RS(w0,amount,w1);
    generate
    genvar k;
    for (k = 0; k < 8; k++)
    assign revw1[k] = w1[7-k];
    endgenerate
    assign revout = select ? w1 : revw1;
endmodule
