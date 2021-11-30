`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 11:50:29 PM
// Design Name: 
// Module Name: Rom_Picker_Mux
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


module Rom_Picker_Mux(
input logic clk, f,
input logic [7:0] in_far, in_cel,
output logic [7:0] data
    );
always_comb
begin
case(f)
0: data = in_cel;
1: data = in_far;
default: data = in_cel;
endcase
end
endmodule