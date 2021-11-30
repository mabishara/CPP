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


void led_check(GpoCore *led_p, Ps2Core *ps2_p, int n) {
   static int i = 0;	// current LED position 0-15
   static int dir = 0;
   char ch;
   int x = 0;
   static int spdnum = 50;
   do {
	led_p->write(0, 0);
	led_p->write(1, i);
	sleep_ms(spdnum);
	led_p->write(0, i);
	sleep_ms(spdnum);
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
		//}
   } while(!ps2_p->get_kb_ch(&ch));
   if(ch == 'p')
   {
	   //pause = !pause;
	   uart.disp("\nPause on");
	   ch = ' ';
	   while(ch != 'p')
	   {
		   ps2_p->get_kb_ch(&ch);
	   }
	   uart.disp("\nPause off");
	   sleep_ms(100);

   }
   else if ((int) ch == -16)
   {
	   uart.disp("\nEnter 3 number value: ");
	   spdnum = 0;
	   while(x < 3)
	   {
		  if(ps2_p->get_kb_ch(&ch))
		  {
			  uart.disp(ch);
			  if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch =='9')
			  {
				  if (x == 0)
				  {
					  spdnum += (ch - 48) * 100;
				  }
				  if (x == 1)
				  {
					  spdnum += (ch - 48) * 10;
				  }
				  if (x == 2)
				  {
					  spdnum += (ch - 48);
				  }
				  x++;
			  }
			  else
			  {
				  uart.disp("\nEnter a value between 0-9 \n");
			  }
		  }
	   }
	   uart.disp("\nThe speed you have chosen is: ");
	   uart.disp(spdnum);
	   uart.disp("\n");
   }
}


void ps2_check(Ps2Core *ps2_p) {
   int id;
   int lbtn, rbtn, xmov, ymov;
   unsigned long last;
   char ch;
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
   } while (now_ms() - last < 2000);
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
ps2_check(&ps2);
   while (1) {
      led_check(&led, &ps2, 16);
   } //while
} //main

