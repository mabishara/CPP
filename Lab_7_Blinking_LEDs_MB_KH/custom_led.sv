//`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/13/2020 11:19:26 PM
// Design Name: 
// Module Name: custom_led
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


module custom_led(
    input clk,
    input reset,
    input [15:0] data,
    output led
    );
    
    logic led_tmp;
    logic [32:0] cnt_limit;
    logic [32:0] count_reg;
    
    always_ff @(posedge clk, posedge reset)
      if (reset)
        begin
          count_reg <= 0;
          led_tmp <= 0;
        end
      else if (count_reg == cnt_limit)
        begin
          count_reg <= 0;
          cnt_limit = data * 100000;
          led_tmp <= ~led_tmp;
        end
      else
        count_reg <= count_reg + 1;
    
    assign led = led_tmp;
    
endmodule