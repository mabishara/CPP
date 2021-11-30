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
void uart_check(double volts);

/**
 * display switch value and corresponding speed
 * @note uart instance is declared as global variable in chu_io_basic.h
 */
void uart_check(double volts) {
   static int loop = 1;

   uart.disp("Speed Change #");
   uart.disp(loop);
   uart.disp(". Current voltage value: ");
   uart.disp(volts);
   uart.disp(".\n");
   loop++;
}
void pwm_3color_led_check(PwmCore *pwm_p, SsegCore *sseg_p, XadcCore *adc_p)
{
	double bright, duty, reading;
	const double colchange = 0.1667;
	reading = adc_p->read_adc_in(0);
	uint8_t num1, num2, num3;
	int ssegread = reading * 1000;
	ssegread /= 10;
	num1 = sseg_p->h2s(ssegread % 10);
	ssegread /= 10;
	num2 = sseg_p->h2s(ssegread % 10);
	ssegread /= 10;
	num3 = sseg_p->h2s(ssegread % 10);
	uint8_t VOLT_PTN[]={num1,num2,num3,0xff,0xff,0xff,0xff,0xff};
	sseg_p->write_8ptn((uint8_t*) VOLT_PTN);
	bright = 50;
	sseg_p->set_dp(0x04);
	duty = bright/100.0;
	static bool potchange = false;
	double oldvolts;
	if (reading < colchange) // 0 - 0.17V
		{
			pwm_p->set_duty(0,0);
			pwm_p->set_duty(((duty*reading)/colchange), 1);
			pwm_p->set_duty(duty, 2);

			pwm_p->set_duty(0,3);
			pwm_p->set_duty(((duty*reading)/colchange), 4);
			pwm_p->set_duty(duty, 5);
		}
	else if (reading - colchange < colchange) // 0.17V - 0.34V
		{
			pwm_p->set_duty(0,0);
			pwm_p->set_duty(duty, 1);
			pwm_p->set_duty(duty -((duty*(reading - colchange))/colchange) , 2);

			pwm_p->set_duty(0,3);
			pwm_p->set_duty(duty, 4);
			pwm_p->set_duty(duty -((duty*(reading - colchange))/colchange), 5);
		}
	else if (reading - (2*colchange) < colchange) // 0.34V - 0.51V
		{
			pwm_p->set_duty(((duty*(reading - (2*colchange)))/colchange), 0);
			pwm_p->set_duty(duty, 1);
			pwm_p->set_duty(0, 2);

			pwm_p->set_duty(((duty*(reading - (2*colchange)))/colchange), 3);
			pwm_p->set_duty(duty, 4);
			pwm_p->set_duty(0, 5);
		}
	else if (reading - (3*colchange) < colchange) // 0.51V - 0.68V
		{
			pwm_p->set_duty(duty, 0);
			pwm_p->set_duty(duty - ((duty*(reading - (3*colchange)))/colchange) , 1);
			pwm_p->set_duty(0, 2);

			pwm_p->set_duty(duty, 3);
			pwm_p->set_duty(duty - ((duty*(reading - (3*colchange)))/colchange) , 4);
			pwm_p->set_duty(0, 5);
		}
	else if (reading - (4*colchange) < colchange) // 0.68V - 0.85V
		{
			pwm_p->set_duty(duty, 0);
			pwm_p->set_duty(0, 1);
			pwm_p->set_duty(((duty*(reading - (4*colchange)))/colchange), 2);

			pwm_p->set_duty(duty, 3);
			pwm_p->set_duty(0 , 4);
			pwm_p->set_duty(((duty*(reading - (4*colchange)))/colchange), 5);

		}
	else if (reading - (5*colchange) < colchange) // 0.85V - 1.02V
		{
			pwm_p->set_duty(duty - ((duty*(reading - (5*colchange)))/colchange), 0);
			pwm_p->set_duty(0, 1);
			pwm_p->set_duty(duty, 2);

			pwm_p->set_duty(duty - ((duty*(reading - (5*colchange)))/colchange), 3);
			pwm_p->set_duty(0, 4);
			pwm_p->set_duty(duty, 5);
		}
	 if (!potchange)
	   {
			oldvolts = reading;	// store current value of potentiometer in oldvolts
			potchange = true;
	   }

	   if ((oldvolts - reading > 0.02) || (reading - oldvolts > 0.02))	// check if old and new speed values do not match
	   {
			uart_check(reading);
			potchange = false;
	   }

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
	while(1){
		pwm_3color_led_check(&pwm, &sseg, &adc);
   } //while
} //main

