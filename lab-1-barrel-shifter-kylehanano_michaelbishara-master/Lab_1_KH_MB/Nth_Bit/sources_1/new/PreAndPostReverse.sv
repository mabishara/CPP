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


module PreAndPostReverse
#(parameter N = 16)
(
    input logic [N-1:0] in,
    input logic [3:0] amount,
    input logic select,
    output logic [N-1:0] revout
    );
    logic [N-1:0] w0, w1, revin, revw1;
    generate
    genvar i;
    for (i = 0; i < N; i++)
    assign revin[i] = in[N-1-i];
    endgenerate
    assign w0 = select ? in : revin;
    RightShifter RS(w0,amount,w1);
    generate
    genvar k;
    for (k = 0; k < N; k++)
    assign revw1[k] = w1[N-1-k];
    endgenerate
    assign revout = select ? w1 : revw1;
endmodule
