`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/13/2020 09:19:13 PM
// Design Name: 
// Module Name: FlipFlop
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


module FlipFlop(
input logic clk,
input logic reset,
input logic fliphigh,
input logic fliplow,
output logic signal
    );
logic start;
always_ff @(posedge clk, posedge reset)
begin
    if (reset || (fliplow && !fliphigh))
        signal <= 0;
        
    else
    begin
        if (fliphigh)
        signal <= 1;
    end
end

endmodule
