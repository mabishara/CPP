`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 11:08:21 PM
// Design Name: 
// Module Name: Rom_Far
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


module Rom_Far(
    input logic clk,
    input logic [7:0] addr,
    output logic [7:0] data
    );
    (*rom_style = "block" *)logic [7:0] rom [0:180];
    initial
        $readmemb("Far_to_Cel.mem", rom);
        
    always_ff @(posedge clk)
        data <= rom[addr];

endmodule
