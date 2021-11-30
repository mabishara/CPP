#include "fifo_core.h"

FifoCore::FifoCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

FifoCore::~FifoCore() {
}
int FifoCore::fifo_empty() {
   uint32_t rd_word;
   int empty;

   rd_word = io_read(base_addr, RD_DATA_REG);
   empty = (int) (rd_word & EMPT_FIELD) >> 8;
   return (empty);
}

int FifoCore::fifo_full() {
   uint32_t rd_word;
   int full;

   rd_word = io_read(base_addr, RD_DATA_REG);
   full = (int) (rd_word & FULL_FIELD) >> 9;
   return (full);
}

void FifoCore::write_byte(uint8_t byte) {
   while (fifo_full()) {
   };  // busy waiting
   io_write(base_addr, WR_DATA_REG, (uint32_t )byte);
}

int FifoCore::read_byte() {
   uint32_t data;

   if (fifo_empty())
      return (-1);
   else {
      data = io_read(base_addr, RD_DATA_REG) & DATA_FIELD;
      io_write(base_addr, EMPTY_DUMMY, 0); //dummy write to remove data from FIFO
      return ((int) data);
   }
}
