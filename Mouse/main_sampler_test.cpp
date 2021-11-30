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

int sw_check(GpiCore *sw_p);
void uart_check(int change, int speed);

void led_check(GpoCore *led_p, GpiCore *sw_p, Ps2Core *ps2_p, int n, int reset) {
	static int i = 0;			// current LED position 0-15
	static int dir = 0;			// LED chase direction
	static int init_toggle = 0;		// initialization
	static bool pause = false;		// pause operation
	static bool sp_change_mode = false;	// speed change mode
	int lbtn, rbtn, xmov, ymov;		// ps2 mouse variables
	double sp_tmp;
	static double speed = 50;
	double sp_change = 0;
	int k;

	if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov))
	{
	   if (lbtn == 1)		// left button press
	   {
	   	pause = !pause;
	   }
	   else if (rbtn == 1)		// right button press
	   {
	   	sp_change_mode = !sp_change_mode;
	   }

	   k = 0;
	   while (sp_change_mode == true)
	   {
		if (k == 0)	// print speed change mode text header only once
		{
			uart.disp("----------------------------------------\n\r");
			uart.disp("Speed change mode on.\n\r\tCurrent speed: ");
			uart.disp(speed);
			uart.disp("ms\n\r\tChange speed by:\n");
			k++;
		}
		else if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov))
		{
			sp_change = xmov*1.765;			// scale xmov to be between 0ms and 450ms (max speed change)
			uart.disp("\r\t\r");			// avoid console spam
			uart.disp(sp_change);			// continuously print speed change values as xmov changes

			if (rbtn == 1)
			{
				sp_tmp = speed + sp_change;	// calculate new speed

				// set speed bounds in the case that xmov returns irregular number
				if (sp_tmp < 50)
				{
				   speed = 50;			// minimum speed of 50ms/pulse
				}
				else if (sp_tmp > 500)
				{
				   speed = 500;			// minimum speed of 500ms/pulse
				}
				else
				{
				   speed = sp_tmp;		// use calculated speed if between 50ms and 500ms
				}

				sp_change_mode = false;		// exit speed change mode
				uart.disp("\n\r\tNew speed: ");
				uart.disp(speed);
				uart.disp("ms\n\r----------------------------------------\n\r");
			}
		}
	   }
	}

   if (pause == false)
   {
	if (reset == 0 && init_toggle == 0)
	{
	   // nothing before initialization
	   uart.disp("Waiting for initialization.\n\r");
	   sleep_ms(500);
	}
	else if (reset == 0 && init_toggle != 0)
	{
		// flash led for proper delay time
		led_p->write(0, 0);
		led_p->write(1, i);
		sleep_ms((int)speed);
		led_p->write(0, i);
		sleep_ms((int)speed);

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
   else
   {
	if (k == 0)	// avoid console spam
	{
		uart.disp("Chasing LEDs operation currently paused at LED ");
		uart.disp(i);
		uart.disp(".\n\r");
		k++;
	}
   }
}

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

void ps2_check(Ps2Core *ps2_p) {
   int id;
   int lbtn, rbtn, xmov, ymov;
   char ch;
   unsigned long last;

   uart.disp("\n\rPS2 device (1-keyboard / 2-mouse): ");
   id = ps2_p->init();
   uart.disp(id);
   uart.disp("\n\r");
   last = now_ms();
   do {
      if (id == 2) {  // mouse
         if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
            uart.disp("[");
            uart.disp(lbtn);
            uart.disp(", ");
            uart.disp(rbtn);
            uart.disp(", ");
            uart.disp(xmov);
            uart.disp(", ");
            uart.disp(ymov);
            uart.disp("] \r\n");
            last = now_ms();

         }   // end get_mouse_activitiy()
      } else {
         if (ps2_p->get_kb_ch(&ch)) {
            uart.disp(ch);
            uart.disp(" ");
            last = now_ms();
         } // end get_kb_ch()
      }  // end id==2
   } while (now_ms() - last < 5000);
   uart.disp("\n\rExit PS2 test \n\r");

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
	int reset = 0;
	int id = 0;

	while (1) {
		if (id != 2)
		{
			uart.disp("\n\rPS2 device (1-keyboard / 2-mouse): ");
			id = ps2.init();
			uart.disp(id);
			uart.disp("\n\r");
		}
		else
		{
			reset = sw_check(&sw);
			led_check(&led, &sw, &ps2, 16, reset);
		}

	//		ps2_check(&ps2);

   } //while
} //main

