`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/01/2020 09:27:58 PM
// Design Name: 
// Module Name: EightBitBS
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


module EightBitBS(
    input logic [31:0] in, 
    input logic [4:0] shift,
    input logic lr,
    output logic [31:0] out
    );
    logic [31:0] w0; logic [31:0] w1;
    RightShifter RS(in, shift, w1);
    LeftShifter LS(in, shift, w0);
    TtOMux LR(w0,w1,lr,out);
    
endmodule
