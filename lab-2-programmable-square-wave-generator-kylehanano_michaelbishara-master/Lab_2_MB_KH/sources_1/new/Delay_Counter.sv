`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/13/2020 08:39:32 PM
// Design Name: 
// Module Name: Delay_Counter
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


module Delay_Counter
#(parameter N=4)
(
input logic clk,
input logic reset,
input logic [N-1:0] m_delay,
input logic [N-1:0] n_delay,
output logic done
    );
logic [N-1:0] m, n, m_next, n_next;
always_ff @(posedge clk, posedge reset)
 begin
    if (reset || done)
    begin
        m <= m_delay;
        n <= n_delay;
    end
    
    else
    begin
        m <= m_next;
        n <= n_next;
    end
 end
assign m_next = (m == 0)? m : m - 1;
assign n_next = (n == 0)? n : n - 1;
assign done = (m == 0 && n == 0);
endmodule
