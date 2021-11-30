/*
 * led_core.cpp
 *
 *  Created on: Oct 14, 2020
 *      Author: Kyle
 */

#include "led_core.h"

LEDCore::LEDCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

LEDCore::~LEDCore() {
}

void LEDCore::write(uint32_t delay_ms, int led) {
   io_write(base_addr, led, delay_ms);
}
