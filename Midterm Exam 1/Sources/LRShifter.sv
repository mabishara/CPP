`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/27/2020 12:55:23 AM
// Design Name: 
// Module Name: LRShifter
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

//Inpsired by Lab 1-barrel shifter's preandpostreverse module
module LRShifter(
input clk, en, reset, m_tick,
output logic [15:0] out
    );
logic [15:0] num;
logic [4:0] countl, countr;
always_ff @(posedge clk, posedge reset)
begin
if(reset || countl == 15 && countr == 15)
    begin
    num <= 1;
    countr <= 0;
    countl <= 0;
    end
else if (en & m_tick)
    begin
        if(countl < 15)
        begin
        num <= {num[14:0],num[15]}; //num << 1;
        countl <= countl + 1;
        countr <= 0;
        end 
        else if(countr < 15)
        begin
        num <= {num[0], num[15:1]};//num >> 1;
        countr <= countr + 1;
        end
     end
end
assign out = num;
endmodule
