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


module BarrelShifterSim();
    reg [31:0] in;
    reg [4:0] shift;
    reg lr;
    wire [31:0] out1;
    wire [31:0] out2;
    EightBitBS uut(in,shift,lr,out1);
    PreAndPostReverse uut2(in,shift,lr,out2);
    initial begin
    #0.55 in = 32'b01111011001010011111000110110001; shift =0; lr = 0;
    #10 shift = 1;
    #10 shift = 2;
    #10 shift = 3;
    #10 shift = 4;
    #10 shift = 5;
    #10 shift = 6;
    #10 shift = 7;
    #10 shift = 8; lr  = 1;
    #10 shift = 1;
    #10 shift = 2;
    #10 shift = 3;
    #10 shift = 4;
    #10 shift = 5;
    #10 shift = 6;
    #10 shift = 7;
    #10 shift = 8;
    #10 $finish;
    end
endmodule
