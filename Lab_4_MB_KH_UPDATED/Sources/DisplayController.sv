`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 03:46:22 AM
// Design Name: 
// Module Name: DisplayController
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

//**MODELED AFTER ECE3300 VERILOG CODE AND TRANSLATED TO SYSTEMVERLIOG**
module DisplayController(
input logic clk,
input logic [11:0] BCD,
output logic [1:0] WADD = 3,
output logic [5:0] DIN,
output logic W
    );
    
localparam inputI = 3;
logic c0, c1, z, ps = 0;
assign z = ~|WADD;

always_comb
    begin
        case(WADD)
        0: DIN <= {1'b1, BCD[3:0], 1'b1};
        1: DIN <= {1'b1, BCD[7:4], 1'b1};
        2: DIN <= {1'b1, BCD[11:8], 1'b1};
        default: DIN <= {1'b1, BCD[3:0], 1'b1};
        endcase
    end

always_ff @(posedge clk)
    begin
        if(c0)
            WADD <= inputI;
        else if (c1)
            WADD <= WADD -1;
    end

always_ff @(posedge clk)
    begin
        case (ps)
        0: ps <= 1;
        1: if (z == 1) ps <= 0; else ps <= 1;
        default: ps <= ps;
        endcase
    end
    
always_comb
    begin
        c0 = ~ps;
        c1 = ps & (~z);
        W = ps;
    end
endmodule
