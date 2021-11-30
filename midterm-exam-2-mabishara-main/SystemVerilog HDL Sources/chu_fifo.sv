module chu_fifo
   #(
   parameter DBIT = 8,      // # data bits
             FIFO_W = 2     // # addr bits of FIFO) // width of input port
    )         
   (
    input  logic clk,
    input  logic reset,
    // slot interface
    input  logic cs,
    input  logic read,
    input  logic write,
    input  logic [4:0] addr,
    input  logic [31:0] wr_data,
    output logic [31:0] rd_data
    // external signal   
   );
    logic [DBIT-1:0] r_data;
    logic full, empty, rd, wr;
   // signal declaration
     fifo #(.DATA_WIDTH(DBIT), .ADDR_WIDTH(FIFO_W))
      (.*, .rd(rd), .wr(wr), .w_data(wr_data[7:0]),
       .empty(empty), .full(full), .r_data(r_data));

 assign rd = (cs && write && (addr[1:0] == 2'b10));
 assign wr = (cs && write && (addr[1:0] == 2'b01));
 assign rd_data = {22'h000000, full,  empty, r_data};
endmodule
