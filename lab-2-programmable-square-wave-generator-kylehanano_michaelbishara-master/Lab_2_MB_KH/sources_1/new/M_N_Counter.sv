`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/13/2020 09:01:41 PM
// Design Name: 
// Module Name: M_N_Counter
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


module M_N_Counter
#(parameter N =4)
(
input logic clk,
input logic reset,
input logic decrement,
input logic [N-1:0] m,
input logic [N-1:0] n,
output logic fliphigh,
output logic fliplow
    );
logic [N-1:0] m_reg, n_reg;
always_ff @(posedge clk, posedge reset)
begin
    if(reset || fliphigh)
    begin
        m_reg <= m;
        n_reg <= n;
    end
    
    else
    begin
        if (decrement)
        begin
        if (fliplow)
            n_reg <= n_reg - 1;
        else
            m_reg <= m_reg - 1;
        end
    end
end
assign fliplow = m_reg == 0;
assign fliphigh = n_reg == 0;
endmodule
