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

module LeftShifter
#(parameter N = 16)
(
    input logic [N-1:0] in,
    input logic [$clog2(N)-1:0] shift,
    output logic [N-1:0] y
    );
    
    localparam M = $clog2(N);
    
    logic [N-1:0] tmp[M:0];     // M+1 by N-1 bits                      
    assign tmp[0] = in;         // set first index of tmp to input value
    assign y = tmp[M];          // set output to final index of tmp     
    
    genvar i;
    generate
      for (i = 0; i < M; i = i + 1) begin
        assign tmp[i+1] = shift[i] ? {tmp[i][(N-1-2**i):0], tmp[i][(N-1):(N-2**i)]} : tmp[i];
      end
    endgenerate
    
endmodule