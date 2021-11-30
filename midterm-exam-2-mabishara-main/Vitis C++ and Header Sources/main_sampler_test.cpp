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
#include "fifo_core.h"
void uart_check(double volts);

/**
 * display switch value and corresponding speed
 * @note uart instance is declared as global variable in chu_io_basic.h
 */
void Fifo_test(FifoCore* fifo_p, SsegCore* sseg_p, XadcCore* adc_p, GpoCore* led_p, DebounceCore* btn_p)
{
	double reading;
	double write = btn_p->read_db(0);
	double read = btn_p->read_db(2);
	reading = adc_p->read_raw(0);
	static int count = 0;
	static bool done_read = false;
	static int sum;
	int ssegsum;
	sseg_p->set_dp(0x00);
	uint8_t num1, num2, num3, num5, num6, num7, num8;
	int ssegread = (reading / 255) - 2;
	int data = (reading / 255) - 2;
	num1 = sseg_p->h2s(ssegread % 10);
	ssegread /= 10;
	num2 = sseg_p->h2s(ssegread % 10);
	ssegread /= 10;
	num3 = sseg_p->h2s(ssegread % 10);
	if(!done_read){
		num5 = 0xff;
		num6 = 0xff;
		num7 = 0xff;
		num8 = 0xff;}
	uint8_t VOLT_PTN[] = { num1, num2, num3, 0xff, num5, num6, num7, num8};
	sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
	if (write)
	{
		if (fifo_p->fifo_full())
		{
			for (int i = 0; i < 4; i++)
			{

				led_p->write(0xffff);
				sleep_ms(50);
				led_p->write(0);
				sleep_ms(50);
			}
			uart.disp("FIFO is full, cannot be written to.\n");
		}
		else
		{
			fifo_p->write_byte(data);
			uart.disp(data);
			uart.disp(" was written into the FIFO at position ");
			uart.disp(count);
			uart.disp(".\n");
			count++;
			sleep_ms(500);
		}

	}
	else if (read)
	{
		if (fifo_p->fifo_empty())
		{
			for (int i = 0; i < 4; i++)
			{

				led_p->write(0xffff);
				sleep_ms(50);
				led_p->write(0);
				sleep_ms(50);
			}
			uart.disp("FIFO is empty, cannot be read from.\n");
		}
		else
		{
			while (!fifo_p->fifo_empty())
			{
				sum += fifo_p->read_byte();
				uart.disp("This is the concurrent sum: ");
				uart.disp(sum);
				uart.disp("\n");
			}
			ssegsum = sum;
			num5 = sseg_p->h2s(ssegsum % 10);
			ssegsum /= 10;
			num6 = sseg_p->h2s(ssegsum % 10);
			ssegsum /= 10;
			num7 = sseg_p->h2s(ssegsum % 10);
			ssegsum /= 10;
			num8 = sseg_p->h2s(ssegsum % 10);
			uart.disp("Total Sum of All Writes: ");
			uart.disp(sum);
			uart.disp("\n");
			sum = 0;
			done_read = true;
			count = 0;
			sleep_ms(500);
		}
	}
	if (fifo_p->fifo_full())
	{
		led_p->write(1, 1);
	}
	else
	{
		led_p->write(0, 1);
	}
	if (fifo_p->fifo_empty()) {
		led_p->write(1, 0);
	}
	else
	{
		led_p->write(0, 0);
	}
}
GpoCore led(get_slot_addr(BRIDGE_BASE, S2_LED));
FifoCore fifo(get_slot_addr(BRIDGE_BASE, S4_USER));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
DebounceCore btn(get_slot_addr(BRIDGE_BASE, S7_BTN));
SsegCore sseg(get_slot_addr(BRIDGE_BASE, S8_SSEG));

int main() {
	while (1) {
		Fifo_test(&fifo, &sseg, &adc, &led, &btn);
	} //while
} //main
