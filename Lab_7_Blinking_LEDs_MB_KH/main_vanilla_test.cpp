/*****************************************************************//**
 * @file main_vanilla_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "led_core.h"


void led_blink(LEDCore *led_p, int i, int delay) {
  led_p->write(delay, i);
}

LEDCore blink(get_slot_addr(BRIDGE_BASE, S4_USER));

int main() {

   while (1) {
	  led_blink(&blink, 0, 500);
	  led_blink(&blink, 1, 1000);
	  led_blink(&blink, 2, 2000);
	  led_blink(&blink, 3, 4000);
   } //while
} //main
