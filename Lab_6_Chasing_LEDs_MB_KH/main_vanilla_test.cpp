/*****************************************************************//**
 * @file main_vanilla_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
int sw_check(GpiCore *sw_p);
void uart_check(int change, int speed);
/**
 * blink once per second for 5 times.
 * provide a sanity check for timer (based on SYS_CLK_FREQ)
 * @param led_p pointer to led instance
 */

/**
 * check individual led
 * @param led_p pointer to led instance
 * @param n number of led
 */

void led_check(GpoCore *led_p, GpiCore *sw_p, int n, int reset) {
   static int i = 0;	// current LED position 0-15
   static int dir = 0;
   static int init_toggle = 0;
   uint8_t mask = 0x3e;
   int swval  = sw_p->read();
   int swvalnew = (swval & mask) >> 1;
   static int temp;
   static int swchange = 0;
   double calc = (swvalnew * 14.516) + 50;

   if (swchange == 0)
   {
		temp = swvalnew;	// store current value of speed switches in temp
		swchange++;
   }

   if (temp != swvalnew)	// check if old and new speed switch values do not match
   {
		uart_check(swvalnew, calc);	// print new value of speed switches
		swchange = 0;
		// toggle swchange back to 0
   }

   if (reset == 0 && init_toggle == 0){
	   // nothing before initialization
   }
   else if (reset == 0 && init_toggle != 0)
   {
	    // flash led for proper delay time
		led_p->write(0, 0);
		led_p->write(1, i);
		sleep_ms((int)calc);
		led_p->write(0, i);
		sleep_ms((int)calc);

		if (i == n-1)
		{
			dir = 1;	// toggle direction if led 15 is on
		}
		else if (i == 0)
		{
			dir = 0;	// toggle direction if led 0 is on
		}

		if (i < n && dir != 1)
		{
			i++;		// increment if direction is left to right
		}
		else
		{
			i--;		// decrement if direction is right to left
		}
   }
   else
   {
	  if (init_toggle == 0)
		  init_toggle++;
      i = 0;
      led_p->write(1, 0);
   }

}

/**
 * checks for reset switch toggle
 * @param sw_p pointer to switch instance
 */
int sw_check(GpiCore *sw_p) {

    uint8_t mask2 = 0x01;
    int sw0 = sw_p->read();
    int sw0new = sw0 & mask2;

    if (sw0new == 1)
       return 1;
    else
    {
       return 0;
    }
}

/**
 * display switch value and corresponding speed
 * @note uart instance is declared as global variable in chu_io_basic.h
 */
void uart_check(int change, int speed) {
   static int loop = 1;

   uart.disp("Speed Change #");
   uart.disp(loop);
   uart.disp(". Current switch value: ");
   uart.disp(change);
   uart.disp(". Speed is: ");
   uart.disp(speed);
   uart.disp(" ms.\n\r");
   loop++;
}

// instantiate switch, led
GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));

int main() {
   int reset;

   while (1)
   {
	 reset = sw_check(&sw);
     led_check(&led, &sw, 16, reset);
   }
}

