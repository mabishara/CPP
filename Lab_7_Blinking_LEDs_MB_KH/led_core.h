/*
 * led_core.h
 *
 *  Created on: Oct 14, 2020
 *      Author: Kyle
 */

#ifndef SRC_LED_CORE_H_
#define SRC_LED_CORE_H_

#include "chu_init.h"

class  LEDCore {
public:
   /**
    * register map
    *
    */
   enum {
      DATA_REG = 0 /**< output data register */
   };
   /**
    * constructor.
    *
    */
   LEDCore(uint32_t core_base_addr);
   ~LEDCore();                  // not used

   /**
    * write a 32-bit word
    * @param data 32-bit data
    *
    */
   void write(uint32_t delay_ms, int led);

private:
   uint32_t base_addr;

};



#endif /* SRC_LED_CORE_H_ */
