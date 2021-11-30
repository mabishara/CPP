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
void recreatePattern(SpiCore *spi_p, GpoCore *led_p, GpiCore *sw_p, SsegCore *sseg_p, int n, float arr[]);

void gsensor_check(SpiCore *spi_p, GpoCore *led_p, GpiCore *sw_p,  SsegCore *sseg_p, int n) {
	const uint8_t RD_CMD = 0x0b;
	const uint8_t DATA_REG = 0x08;
	static bool msg = false;
	static bool start = false;
	static bool maxsig = false;
    float oldzread = 0;
    static bool initial = true;
	static float oldz;
	const float raw_max = 127.0 / 2.0;	//128 max 8-bit reading for +/-2g
	float x, y, z;
	float array[n];
	static int i = 0;
	int8_t xraw, yraw, zraw;
	uint8_t VOLT_PTN[] = { 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf};		// segment g on for each sseg
	uint8_t NULL_PTN[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};		// all segments off for each sseg
	if (initial){
		for (int q = 0; q < 5; q++){
			spi_p->assert_ss(0);		// activate
			spi_p->transfer(RD_CMD);	// for read operation
			spi_p->transfer(DATA_REG);	//
			xraw = spi_p->transfer(0x00);
			yraw = spi_p->transfer(0x00);
			zraw = spi_p->transfer(0x00);
			spi_p->deassert_ss(0);
			x = (float) xraw / raw_max;
			y = (float) yraw / raw_max;
			z = (float) zraw / raw_max;
			oldzread += z;
		}
		oldzread /= 5;
		initial = false;
		oldz = oldzread;
	}

	sseg_p->set_dp(0x00);
	spi_p->set_freq(400000);
	spi_p->set_mode(0, 0);

	if(!maxsig)
	{
		led_p -> write(0);
		sleep_ms(3000);
		led_p->write(i);
		sleep_ms(500);
	}

	if (n != i) {
		sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
		sleep_ms(750);
		spi_p->assert_ss(0);		// activate
		spi_p->transfer(RD_CMD);	// for read operation
		spi_p->transfer(DATA_REG);
		xraw = spi_p->transfer(0x00);
		yraw = spi_p->transfer(0x00);
		zraw = spi_p->transfer(0x00);
		spi_p->deassert_ss(0);
		x = (float) xraw / raw_max;
		y = (float) yraw / raw_max;
		z = (float) zraw / raw_max;


		while(((z - oldz < 0.03) && (oldz - z < 0.03)) && !start) {
			spi_p->assert_ss(0);		// activate
			spi_p->transfer(RD_CMD);	// for read operation
			spi_p->transfer(DATA_REG);	//
			xraw = spi_p->transfer(0x00);
			yraw = spi_p->transfer(0x00);
			zraw = spi_p->transfer(0x00);
			spi_p->deassert_ss(0);
			x = (float) xraw / raw_max;
			y = (float) yraw / raw_max;
			z = (float) zraw / raw_max;
		}

		sseg_p->write_8ptn((uint8_t*)NULL_PTN);
		start = true;
		uart.disp("z = ");
		uart.disp(z);

		if (((z - oldz < 0.03) && (oldz - z < 0.03))) {
			array[i] = 0;
			uart.disp(" (No Tap)");
		}
		else {
			array[i] = 1;
			uart.disp(" (Tap)");
		}

		i++;
		uart.disp("\n");
	}
	else {
		maxsig = true;
		led_p->write(0x8000);
		if (!msg)
			uart.disp("Flip switch 16 to toggle to detection mode.\n");
		msg = true;
		if (sw_p->read(15))
		{
			uart.disp("Beginning recreation sequence...\n");
			while ((sw_p->read(15)))
				recreatePattern(spi_p, led_p, sw_p, sseg_p, n, array);
		}
	}
}

void recreatePattern(SpiCore *spi_p, GpoCore *led_p, GpiCore *sw_p, SsegCore *sseg_p,  int n, float arr[]) {
	const uint8_t RD_CMD = 0x0b;
	const uint8_t DATA_REG = 0x08;
	const float raw_max = 127.0 / 2.0;  //128 max 8-bit reading for +/-2g
	static int k = 0;
	sseg_p->set_dp(0x00);
	static bool toggle = false;
	static bool rerun = false;\
	uint8_t VOLT_PTN[] = { 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf};
	uint8_t NULL_PTN[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	int8_t xraw, yraw, zraw;
	float x, y, z;
	float array[n];
	int equalscnt = 0;
	static bool maxsig2 = false;
	static bool initial = true;
    static float oldz;
    float oldzread = 0;
	spi_p->set_freq(400000);
	spi_p->set_mode(0, 0);
	if (initial){
			for (int q = 0; q < 5; q++){
				spi_p->assert_ss(0);		// activate
				spi_p->transfer(RD_CMD);	// for read operation
				spi_p->transfer(DATA_REG);	//
				xraw = spi_p->transfer(0x00);
				yraw = spi_p->transfer(0x00);
				zraw = spi_p->transfer(0x00);
				spi_p->deassert_ss(0);
				x = (float) xraw / raw_max;
				y = (float) yraw / raw_max;
				z = (float) zraw / raw_max;
				oldzread += z;
			}
			oldzread /= 5;
			initial = false;
			oldz = oldzread;
		}
	if(!maxsig2) {
		sleep_ms(3500);
	}

	if (n != k) {
		sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
		sleep_ms(750);

		spi_p->assert_ss(0);    // activate
		spi_p->transfer(RD_CMD);  // for read operation
		spi_p->transfer(DATA_REG);  //
		xraw = spi_p->transfer(0x00);
		yraw = spi_p->transfer(0x00);
		zraw = spi_p->transfer(0x00);
		spi_p->deassert_ss(0);
		x = (float) xraw / raw_max;
		y = (float) yraw / raw_max;
		z = (float) zraw / raw_max;

		while(((z - oldz < 0.03) && (oldz - z < 0.03) ) && !rerun){
			spi_p->assert_ss(0);    // activate
			spi_p->transfer(RD_CMD);  // for read operation
			spi_p->transfer(DATA_REG);  //
			xraw = spi_p->transfer(0x00);
			yraw = spi_p->transfer(0x00);
			zraw = spi_p->transfer(0x00);
			spi_p->deassert_ss(0);
			x = (float) xraw / raw_max;
			y = (float) yraw / raw_max;
			z = (float) zraw / raw_max;
		}

		sseg_p->write_8ptn((uint8_t*)NULL_PTN);
		rerun = true;
		uart.disp("z = ");
		uart.disp(z);

		if (((z - oldz < 0.03) && (oldz - z < 0.03) )) {
			array[k] = 0;
			uart.disp(" (No Tap)");
		}
		else {
			array[k] = 1;
			uart.disp(" (Tap)");
		}

		k++;
		uart.disp("\n");
	}
	else {
		maxsig2 = true;
		for(int w = 0; w < n; w++) {
			if (arr[w] == array[w]) {
				equalscnt++;
			}
		}
		if (equalscnt == n) {
			if (!toggle) {
				led_p->write(0xffff);
			}
			else {
				led_p->write(0);
			}
			rerun = false;
			maxsig2 = false;
			k = 0;
			toggle = !toggle;
			uart.disp("Rerunning Pattern Recreation Sequence...\n");
			sleep_ms(5000);
			recreatePattern(spi_p, led_p, sw_p, sseg_p, n, arr);
		}
		else {
			uart.disp("The two sequences did not match, try again by tapping.");
			uart.disp("\n");
			rerun = false;
			maxsig2 = false;
			k = 0;
			uart.disp("Rerunning Pattern Recreation Sequence...\n");
			sleep_ms(5000);
			recreatePattern(spi_p, led_p, sw_p, sseg_p, n, arr);
		}
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
   while (1) {
      gsensor_check(&spi, &led, &sw, &sseg, 4);
   }
}

