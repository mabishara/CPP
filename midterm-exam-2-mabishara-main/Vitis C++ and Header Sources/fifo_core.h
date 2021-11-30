/*
 * led_core.h
 */

#ifndef _FIFO_CORE_H_INCLUDED
#define _FIFO_CORE_H_INCLUDED

#include "chu_init.h"
#include "chu_io_rw.h"
#include "chu_io_map.h"  // to use SYS_CLK_FREQ

class  FifoCore {
public:
   /**
    * register map
    *
    */
   enum {
      RD_DATA_REG = 0, /**< output data register */
	  WR_DATA_REG = 1, /**< wr data register */
	  EMPTY_DUMMY = 2
   };
   enum {
         FULL_FIELD = 0x00000200, /**< bit 9 of rd_data_reg; full bit  */
         EMPT_FIELD = 0x00000100, /**< bit 10 of rd_data_reg; empty bit */
         DATA_FIELD = 0x000000ff  /**< bits 7..0 rd_data_reg; read data */
      };
   /**
    * constructor.
    *
    */
   FifoCore(uint32_t core_base_addr);
   ~FifoCore();                  // not used

   /**
      * check whether fifo is empty
      *
      * @return 1: if empty; 0: otherwise
      *
      */
     int fifo_empty();

     /**
      * check whether fifo is full
      *
      * @return 1: if full; 0: otherwise
      *
      */
     int fifo_full();

     /**
      * write a byte
      *
      * @param byte data byte to be transmitted
      *
      * @note the function "busy waits" if fifo is full;
      *       to avoid "blocking" execution, use fifo_full() to check status as needed
      */
     void write_byte(uint8_t byte);

     /**
      * read a byte
      *
      * @return -1 if rx fifo empty; byte data other wise
      *
      * @note the function does not "busy wait"
      */
     int read_byte();


private:
   uint32_t base_addr;

};

#endif /* SRC_FIFO_CORE_H_ */
