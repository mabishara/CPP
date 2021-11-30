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
    reg [7:0] in;
    reg [2:0] shift;
    reg lr;
    wire [7:0] out;
    PreAndPostReverse uut2(in,shift,lr,out);
    initial begin
    #0.55 in = 8'b10011010; shift =0; lr = 0;
    #10 shift = 1;
    #10 shift = 2;
    #10 shift = 3; lr  = 1;
    #10 shift = 1;
    #10 shift = 2;    
    #10 $finish;
    end
endmodule
