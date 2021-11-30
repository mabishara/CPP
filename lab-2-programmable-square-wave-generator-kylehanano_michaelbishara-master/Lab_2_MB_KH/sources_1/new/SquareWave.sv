`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/07/2020 11:27:27 PM
// Design Name: 
// Module Name: SquareWave
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


module SquareWave
#(parameter N=4)
(
    input logic clk,
    input logic reset,
    input logic [N-1:0] m,
    input logic [N-1:0] n,
    output logic q
    );
    
    localparam counter = 9;
    logic delay_done;
    logic fh, fl;
    
    Delay_Counter d_counter(.clk(clk), .reset(reset), .m_delay(counter), .n_delay(counter), .done(delay_done));
    M_N_Counter mn_counter(.clk(clk), .reset(reset), .decrement(delay_done), .m(m), .n(n), .fliphigh(fh), .fliplow(fl));
    FlipFlop ff(.clk(clk), .reset(reset), .fliphigh(fh), .fliplow(fl), .signal(q));
    
endmodule
