`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/01/2020 10:17:05 PM
// Design Name: 
// Module Name: BarrelShifterSim
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


module BarrelShifterSim
#(parameter N=16)
();
    reg [N-1:0] in;
    reg [3:0] shift;
    reg lr;
    wire [N-1:0] out1;
    wire [N-1:0] out2;
    EightBitBS uut(in,shift,lr,out1);
    PreAndPostReverse uut2(in,shift,lr,out2);
    initial begin
    #0.55 in = 16'b1000100100000001; shift =0; lr = 0;
    #10 shift = 1;
    #10 shift = 2;
    #10 shift = 3;
    #10 shift = 4; lr  = 1;
    #10 shift = 1;
    #10 shift = 2;
    #10 shift = 3;
    #10 shift = 4;    
    #10 $finish;
    end
endmodule
