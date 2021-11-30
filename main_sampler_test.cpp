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


void adt7420_check(I2cCore *adt7420_p, SsegCore *sseg_p, DebounceCore *btn_p) {
   const uint8_t DEV_ADDR = 0x4b;
   const uint8_t PatternF = 0x8e;
   const uint8_t PatternC = 0xc6;
   uint8_t wbytes[2], bytes[2];
   uint16_t tmp;
   float tmpC;
   float tmpF;
   double btnu = btn_p->read_db(0);
   double btnr = btn_p->read_db(1);
   double btnd = btn_p->read_db(2);
   double btnl = btn_p->read_db(3);
   uint8_t num1, num2, num3, num4, num5, num6, num7, num8;
   int ssegread, ssegread2;
   wbytes[0] = 0x00;
   adt7420_p->write_transaction(DEV_ADDR, wbytes, 1, 1);
   adt7420_p->read_transaction(DEV_ADDR, bytes, 2, 0);
   tmp = (uint16_t) bytes[0];
   tmp = (tmp << 8) + (uint16_t) bytes[1];

   if (tmp & 0x8000) {
      tmp = tmp >> 3;
      tmpC = (float) ((int) tmp - 8192) / 16;
   }
   else {
      tmp = tmp >> 3;
      tmpC = (float) tmp / 16;
   }

   tmpF = (tmpC * (9.0/5.0)) + 32;
   if (btnu){
	   ssegread = tmpC*100;
	   num1 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num2 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num3 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num4 = sseg_p->h2s(ssegread % 10);
	   uint8_t VOLT_PTN[] = { 0xFF, 0xFF, 0xFF, PatternC, num1, num2, num3, num4};
	   sseg_p->set_dp(0x40);
	   sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
	   uart.disp("temperature (C): ");
	   uart.disp(tmpC);
	   uart.disp("\n\r");
	   sleep_ms(500);
   }
   if (btnd){
	   ssegread = tmpF*100;
	   num1 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num2 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num3 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num4 = sseg_p->h2s(ssegread % 10);
	   uint8_t VOLT_PTN[] = { 0xFF, 0xFF, 0xFF, PatternF, num1, num2, num3, num4};
	   sseg_p->set_dp(0x40);
	   sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
	   uart.disp("temperature (F): ");
	   uart.disp(tmpF);
	   uart.disp("\n\r");
	   sleep_ms(500);
   }
   if(btnl){
	   ssegread = tmpF*100;
	   num1 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num2 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num3 = sseg_p->h2s(ssegread % 10);
	   ssegread /= 10;
	   num4 = sseg_p->h2s(ssegread % 10);
	   ssegread2 = tmpC*100;
	   num5 = sseg_p->h2s(ssegread2 % 10);
	   ssegread2 /= 10;
	   num6 = sseg_p->h2s(ssegread2 % 10);
	   ssegread2 /= 10;
	   num7 = sseg_p->h2s(ssegread2 % 10);
	   ssegread2 /= 10;
	   num8 = sseg_p->h2s(ssegread2 % 10);
	   uint8_t VOLT_PTN[] = { num5, num6, num7, num8, num1, num2, num3, num4};
	   sseg_p->set_dp(0x44);
	   sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
	   uart.disp("temperature (F): ");
	   uart.disp(tmpF);
	   uart.disp("\n\r");
	   uart.disp("temperature (C): ");
	   uart.disp(tmpC);
	   uart.disp("\n\r");
	   sleep_ms(500);
   }
   if(btnr){
	   uint8_t VOLT_PTN[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	   sseg_p->set_dp(0x00);
	   sseg_p->write_8ptn((uint8_t*)VOLT_PTN);
	   sleep_ms(500);
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
   //uint8_t id, ;

   while (1) {
      adt7420_check(&adt7420, &sseg, &btn);
   } //while
} //main
