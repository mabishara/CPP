//`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/13/2020 09:37:15 PM
// Design Name: 
// Module Name: chu_led
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


module chu_led
   #(parameter W = 4)  // width of output port
   (
    input  logic clk,
    input  logic reset,
    // slot interface
    input  logic cs,
    input  logic read,
    input  logic write,
    input  logic [4:0] addr,
    input  logic [31:0] wr_data,
    output logic [31:0] rd_data,
    // external port
    output logic [W-1:0] dout
   );

   // signal declaration
   logic wr_en;
   logic [15:0] delay0, delay1, delay2, delay3;
   logic led0, led1, led2, led3;
   
   //***************************************************************
   // LED delay counters
   //***************************************************************   
   custom_led u1(.clk(clk), .reset(reset), .data(delay0), .led(led0));
   custom_led u2(.clk(clk), .reset(reset), .data(delay1), .led(led1));
   custom_led u3(.clk(clk), .reset(reset), .data(delay2), .led(led2));
   custom_led u4(.clk(clk), .reset(reset), .data(delay3), .led(led3));
   
   //***************************************************************
   // wrapping circuit
   //***************************************************************

  always_ff @(posedge clk, posedge reset)
  begin
    if (reset)
      begin
        delay0 <= 0;
        delay1 <= 0;
        delay2 <= 0;
        delay3 <= 0;
      end
    else
      begin
        if (addr == 0 && wr_en)
          delay0 <= wr_data [15:0];
        else if (addr == 1 && wr_en)
          delay1 <= wr_data [15:0];
        else if (addr == 2 && wr_en)
          delay2 <= wr_data [15:0];
        else if (addr == 3 && wr_en)
          delay3 <= wr_data [15:0];
       end
  end
  
  // decoding logic
  assign wr_en = write && cs;
  // slot read interface
  assign rd_data =  0;
  
  assign dout = {led3, led2, led1, led0};
  
   
endmodule
