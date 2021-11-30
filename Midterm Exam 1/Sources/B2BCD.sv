`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2020 01:25:09 AM
// Design Name: 
// Module Name: B2BCD
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

//**MODELED AFTER A B2BCD MOUDLE FROM NANLAND.COM TRANSLATED TO SYSTEMVERILOG WITH SIGNIFICANT MODIFICATION**
module B2BCD(
input logic clk,
input logic [7:0] binary,
output logic [11:0] BCD
    );
    
  localparam s_IDLE = 3'b000;
  localparam s_SHIFT = 3'b001;
  localparam s_CHECK_SHIFT_INDEX = 3'b010;
  localparam s_ADD = 3'b011;
  localparam s_CHECK_DIGIT_INDEX = 3'b100;
  localparam s_BCD_DONE = 3'b101;
   
  logic [2:0] r_SM_Main = s_IDLE;

  // The vector that contains the output BCD
  logic [11:0] r_BCD;
  logic [7:0] temp_Binary = 0;
  logic start;
  
  // The vector that contains the input binary value being shifted.
  logic [7:0] r_Binary;
      
  // Keeps track of which Decimal Digit we are indexing
  logic [11:0] r_Digit_Index;
    
  // Keeps track of which loop iteration we are on.
  logic [7:0] r_Loop_Count;
  logic [3:0] w_BCD_Digit;
  logic r_DV;                       
    
  always @(posedge clk)
    begin
    
      case (r_SM_Main) 
  
        // Stay in this state until start comes along
        s_IDLE :
          begin
            r_DV <= 1'b0;
            r_Digit_Index <= 0;
            r_Loop_Count <= 0;
            if (start == 1'b1)
             begin
                temp_Binary <= binary;
                r_Binary  <= binary;
                r_SM_Main <= s_SHIFT;
                r_BCD     <= 0;
              end
           else
              r_SM_Main <= s_IDLE;
         end
                 
  
        // Always shift the BCD Vector until we have shifted all bits through
        // Shift the most significant bit of r_Binary into r_BCD lowest bit.
        s_SHIFT :
          begin
            r_BCD     <= r_BCD << 1;
            r_BCD[0]  <= r_Binary[7];
            r_Binary  <= r_Binary << 1;
            r_SM_Main <= s_CHECK_SHIFT_INDEX;
          end          
         
  
        // Check if we are done with shifting in r_Binary vector
        s_CHECK_SHIFT_INDEX :
          begin
            if (r_Loop_Count == 7)
              begin
                r_Loop_Count <= 0;
                r_SM_Main    <= s_BCD_DONE;
              end
            else
              begin
                r_Loop_Count <= r_Loop_Count + 1;
                r_SM_Main    <= s_ADD;
              end
          end
                 
  
        // Break down each BCD Digit individually.  Check them one-by-one to
        // see if they are greater than 4.  If they are, increment by 3.
        // Put the result back into r_BCD Vector.  
        s_ADD :
          begin
            if (w_BCD_Digit > 4)
              begin                                     
                r_BCD[(r_Digit_Index*4)+:4] <= w_BCD_Digit + 3;  
              end
             
            r_SM_Main <= s_CHECK_DIGIT_INDEX; 
          end       
         
         
        // Check if we are done incrementing all of the BCD Digits
        s_CHECK_DIGIT_INDEX :
          begin
            if (r_Digit_Index == 2)
              begin
                r_Digit_Index <= 0;
                r_SM_Main     <= s_SHIFT;
              end
            else
              begin
                r_Digit_Index <= r_Digit_Index + 1;
                r_SM_Main     <= s_ADD;
              end
          end
         
  
  
        s_BCD_DONE :
          begin
            r_DV      <= 1'b1;
            r_SM_Main <= s_IDLE;
          end
         
         
        default :
          r_SM_Main <= s_IDLE;
            
      endcase
    end 
 
 
  assign w_BCD_Digit = r_BCD[r_Digit_Index*4 +: 4];
  assign start = (binary != temp_Binary);
  assign BCD = r_BCD;
  
endmodule

