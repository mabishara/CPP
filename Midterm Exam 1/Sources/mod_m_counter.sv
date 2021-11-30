`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/26/2020 01:33:43 PM
// Design Name: 
// Module Name: mod_m_counter
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

//Mod counter that takes an input. Inspired by mod_m_counter with parameter M
module mod_m_counter
    (
        input logic [25:0] in,
        input logic clk, reset, en,
        output logic max_tick
    );
    logic [25:0] r_next, r_reg;
    logic [25:0] temp;
    always_ff @(posedge clk, posedge reset)
    begin
        if(reset)
        begin
            r_reg <= 0;
            temp <= in;
        end
        else if (temp != in)
        temp <= in;
        else
        if (en)
            r_reg <= r_next;
        else
            r_reg <= 0;
    end
    
    assign r_next = (r_reg == temp)? 0: r_reg + 1;
    
    assign max_tick = (r_reg == temp) ? 1'b1: 1'b0;
    
endmodule