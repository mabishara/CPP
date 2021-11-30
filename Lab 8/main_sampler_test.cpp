/*****************************************************************//**
 * @file main_sampler_test.cpp
 *
 * @brief Basic test of nexys4 ddr mmio cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

// #define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"
#include "sseg_core.h"
#include "spi_core.h"
#include "i2c_core.h"
#include "ps2_core.h"
#include "ddfs_core.h"
#include "adsr_core.h"
void uart_check(double volts, double speed);

void led_check(GpoCore *led_p, XadcCore *adc_p, int n, bool reset) {
   static int i = 0; // current LED position 0-15
   static int dir = 0;
   int k;
   double reading;
   static bool init_toggle = false;
   static double temp;
   static int swchange = 0;
   double calc = 0;
   double volts = 0;
   for (k = 0; k < 4; k++) {
            reading = adc_p->read_adc_in(k);
            volts += reading;
   }
   calc = (volts * 450.0) + 50;
   if (swchange == 0)
   {
		temp = volts;	// store current value of speed switches in temp
		swchange++;
   }

   if (temp != volts)	// check if old and new speed switch values do not match
   {
	   if (init_toggle && !reset){
		uart_check(volts, calc);
	   }// print new value of speed switches
		swchange = 0;
		// toggle swchange back to 0
   }

   if (!reset && !init_toggle){
	   // nothing before initialization
   }
   else if (!reset && init_toggle)
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
	  if (!init_toggle)
		  init_toggle = true;
      i = 0;
      led_p->write(1, 0);
   }

}

/**
 * checks for reset switch toggle
 * @param sw_p pointer to switch instance
 */
bool sw_check(GpiCore *sw_p) {

    uint8_t mask2 = 0x01;
    int sw0 = sw_p->read();
    int sw0new = sw0 & mask2;

    if (sw0new == 1)
       return true;
    else
    {
       return false;
    }
}

/**
 * display switch value and corresponding speed
 * @note uart instance is declared as global variable in chu_io_basic.h
 */
void uart_check(double volts, double speed) {
   static int loop = 1;

   uart.disp("Speed Change #");
   uart.disp(loop);
   uart.disp(". Current voltage value: ");
   uart.disp(volts);
   uart.disp(". Speed is: ");
   uart.disp(speed);
   uart.disp(" ms.\n\r");
   loop++;
}

GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
PwmCore pwm(get_slot_addr(BRIDGE_BASE, S6_PWM));
DebounceCore btn(get_slot_addr(BRIDGE_BASE, S7_BTN));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));
SpiCore spi(get_slot_addr(BRIDGE_BASE, S9_SPI));
I2cCore adt7420(get_slot_addr(BRIDGE_BASE, S10_I2C));
Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));
DdfsCore ddfs(get_slot_addr(BRIDGE_BASE, S12_DDFS));
AdsrCore adsr(get_slot_addr(BRIDGE_BASE, S13_ADSR), &ddfs);


int main() {
	bool reset;
   while (1) {
	   reset = sw_check(&sw);
	   led_check(&led, &adc, 16, reset);

   } //while
} //main

