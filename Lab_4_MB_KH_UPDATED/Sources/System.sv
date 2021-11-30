`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 03:58:59 AM
// Design Name: 
// Module Name: System
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
module System(
input logic [5:0] DIN,
input logic [1:0] WADD,
input logic W, clk,
output logic [7:0] E,
output logic [6:0] CA2G,
output logic dp
    );

logic[19:0] Counter = 0; 
logic [5:0] DOUT;
logic [5:0] DOUT0;
logic [5:0] DOUT1; 
logic [5:0] DOUT2; 
logic [3:0] Y; 

always_comb
    begin
        if(W)
            case(WADD)
            0: Y = 8'h01;
            1: Y = 8'h02;
            2: Y = 8'h04;
            default Y = 8'h00;
            endcase
        else
            Y = 0;
    end
    
always_ff @(posedge clk)
    begin
    Counter <= Counter + 1;
     if (Y[0] == 1)
        DOUT0 <=DIN;
     if (Y[1] == 1)
        DOUT1 <=DIN;
     if (Y[2] == 1)
        DOUT2 <=DIN;
    end

always_comb
    begin
         case(Counter[19:17])
         3'b000: begin DOUT = DOUT0; E = 8'hFE; end
         3'b001: begin DOUT = DOUT1; E = 8'hFD; end
         3'b010: begin DOUT = DOUT2; E = 8'hFB; end
         default: begin DOUT = DOUT; E = 8'hFF; end 
         endcase
     end
     
assign dp = DOUT[0];

always_comb
     begin
         if (DOUT[5])
               case(DOUT[4:1])
                   4'h0: CA2G <= 7'b0000001;
                   4'h1: CA2G <= 7'b1001111;
                   4'h2: CA2G <= 7'b0010010;
                   4'h3: CA2G <= 7'b0000110;
                   4'h4: CA2G <= 7'b1001100;
                   4'h5: CA2G <= 7'b0100100;
                   4'h6: CA2G <= 7'b0100000;
                   4'h7: CA2G <= 7'b0001111;
                   4'h8: CA2G <= 7'b0000000;
                   4'h9: CA2G <= 7'b0000100;
                   4'hA: CA2G <= 7'b0000010;
                   4'hB: CA2G <= 7'b1100000;
                   4'hC: CA2G <= 7'b0110001;
                   4'hD: CA2G <= 7'b1000010;
                   4'hE: CA2G <= 7'b0110000;
                   4'hF: CA2G <= 7'b0111000;
                   default: CA2G <= 7'b1111111;
               endcase
         else CA2G <= 7'b1111111;
     end
endmodule
