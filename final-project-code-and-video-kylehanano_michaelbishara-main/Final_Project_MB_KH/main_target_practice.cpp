// Original
/*****************************************************************//**
 * @file main_video_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"
#include "xadc_core.h"
#include "ps2_core.h"
#include "vga_core.h"

enum letters {A=1, B=2, C=3, D=4, E=5, F=6, G=7, H=8, I=9, J=10, K=11, L=12, M=13, N=14, O=15, P=16, Q=17, R=18, S=19, T=20, U=21, V=22, W=23, X=24, Y=25, Z=26};
enum buttons {btn_u=0, btn_r=1, btn_d=2, btn_l=3, btn_c=4};

void mouse_check_2(SpriteCore *mouse_p, Ps2Core *ps2_p) {
	const int xmax = 649;
	const int ymax = 479;
	static int x = 0;
	static int y = 0;
	int tmp_x;
	int tmp_y;
	int lbtn, rbtn, xmov, ymov;

	if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
		tmp_x = x + xmov;
		tmp_y = y - ymov;

		if(0 <= tmp_x && tmp_x <= xmax) {
		   x = tmp_x;
		}

		if(0 <= tmp_y && tmp_y <= ymax) {
		   y = tmp_y;
		}

		mouse_p->move_xy(x, y);
	}
}

void osd_check(OsdCore *osd_p) {
   osd_p->set_color(0x0f0, 0x001); // dark gray/green
   osd_p->bypass(0);
   osd_p->clr_screen();
   for (int i = 0; i < 64; i++) {
      osd_p->wr_char(8 + i, 20, i);
      osd_p->wr_char(8 + i, 21, 64 + i, 1);
      sleep_ms(100);
   }
   sleep_ms(3000);
}

void main_screen_animation(SpriteCore *ghost_p, SpriteCore *mouse_p) {
	static bool dir = 0;		// 0 = right, 1 = left
	static int x = 280;	// poll from 300 to 340
	const int ghost_y = 220;
	const int mouse_y = 240;
	const int mouse_x_offset = 8;

	mouse_p->bypass(0);
	ghost_p->bypass(0);
	ghost_p->wr_ctrl(0x01);
	ghost_p->move_xy(x,ghost_y);

	if ((dir == 1 and x == 280) or (dir == 0 and x == 360)) {
		dir = !dir;
	}

	if (dir == 0) {
		ghost_p->move_xy(x, ghost_y);
		mouse_p->move_xy(x+mouse_x_offset, mouse_y);
		x = x + 5;
	}
	else {
		ghost_p->move_xy(x, ghost_y);
		mouse_p->move_xy(x+mouse_x_offset, mouse_y);
		x = x - 5;
	}

	sleep_ms(150);
}

void main_screen_disp(OsdCore *osd_p) {
	const int left_offset = 2;
	const int top_offset = 1;

	osd_p->set_color(0x0f0, 0x001); // dark gray/green
	osd_p->bypass(0);
	osd_p->clr_screen();

	// Display Game Title
	osd_p->wr_char(30 + 0, 10, 64 + T);
	osd_p->wr_char(30 + 1, 10, 96 + A);
	osd_p->wr_char(30 + 2, 10, 96 + R);
	osd_p->wr_char(30 + 3, 10, 96 + G);
	osd_p->wr_char(30 + 4, 10, 96 + E);
	osd_p->wr_char(30 + 5, 10, 96 + T);
	osd_p->wr_char(30 + 6, 10, 0);
	osd_p->wr_char(30 + 7, 10, 64 + P);
	osd_p->wr_char(30 + 8, 10, 96 + R);
	osd_p->wr_char(30 + 9, 10, 96 + A);
	osd_p->wr_char(30 + 10, 10, 96 + C);
	osd_p->wr_char(30 + 11, 10, 96 + T);
	osd_p->wr_char(30 + 12, 10, 96 + I);
	osd_p->wr_char(30 + 13, 10, 96 + C);
	osd_p->wr_char(30 + 14, 10, 96 + E);
	osd_p->wr_char(30 + 15, 10, 0);
	osd_p->wr_char(30 + 16, 10, 64 + G);
	osd_p->wr_char(30 + 17, 10, 96 + A);
	osd_p->wr_char(30 + 18, 10, 96 + M);
	osd_p->wr_char(30 + 19, 10, 96 + E);

	// Display prompt for start button
	osd_p->wr_char(31 + 0, 20, 64 + P);
	osd_p->wr_char(31 + 1, 20, 96 + R);
	osd_p->wr_char(31 + 2, 20, 96 + E);
	osd_p->wr_char(31 + 3, 20, 96 + S);
	osd_p->wr_char(31 + 4, 20, 96 + S);
	osd_p->wr_char(31 + 5, 20, 0);
	osd_p->wr_char(31 + 6, 20, 64 + B);
	osd_p->wr_char(31 + 7, 20, 64 + T);
	osd_p->wr_char(31 + 8, 20, 64 + N);
	osd_p->wr_char(31 + 9, 20, 64 + C);
	osd_p->wr_char(31 + 10, 20, 0);
	osd_p->wr_char(31 + 11, 20, 64 + T);
	osd_p->wr_char(31 + 12, 20, 96 + O);
	osd_p->wr_char(31 + 13, 20, 0);
	osd_p->wr_char(31 + 14, 20, 64 + S);
	osd_p->wr_char(31 + 15, 20, 96 + T);
	osd_p->wr_char(31 + 16, 20, 96 + A);
	osd_p->wr_char(31 + 17, 20, 96 + R);
	osd_p->wr_char(31 + 18, 20, 96 + T);

	// Print Names and Course
	osd_p->wr_char(left_offset + 0, top_offset, 64 + M);
	osd_p->wr_char(left_offset + 1, top_offset, 96 + I);
	osd_p->wr_char(left_offset + 2, top_offset, 96 + C);
	osd_p->wr_char(left_offset + 3, top_offset, 96 + H);
	osd_p->wr_char(left_offset + 4, top_offset, 96 + A);
	osd_p->wr_char(left_offset + 5, top_offset, 96 + E);
	osd_p->wr_char(left_offset + 6, top_offset, 96 + L);
	osd_p->wr_char(left_offset + 7, top_offset, 0);
	osd_p->wr_char(left_offset + 8, top_offset, 64 + B);
	osd_p->wr_char(left_offset + 9, top_offset, 96 + I);
	osd_p->wr_char(left_offset + 10, top_offset, 96 + S);
	osd_p->wr_char(left_offset + 11, top_offset, 96 + H);
	osd_p->wr_char(left_offset + 12, top_offset, 96 + A);
	osd_p->wr_char(left_offset + 13, top_offset, 96 + R);
	osd_p->wr_char(left_offset + 14, top_offset, 96 + A);

	osd_p->wr_char(left_offset + 0, top_offset + 1, 64 + K);
	osd_p->wr_char(left_offset + 1, top_offset + 1, 96 + Y);
	osd_p->wr_char(left_offset + 2, top_offset + 1, 96 + L);
	osd_p->wr_char(left_offset + 3, top_offset + 1, 96 + E);
	osd_p->wr_char(left_offset + 4, top_offset + 1, 0);
	osd_p->wr_char(left_offset + 5, top_offset + 1, 64 + H);
	osd_p->wr_char(left_offset + 6, top_offset + 1, 96 + A);
	osd_p->wr_char(left_offset + 7, top_offset + 1, 96 + N);
	osd_p->wr_char(left_offset + 8, top_offset + 1, 96 + A);
	osd_p->wr_char(left_offset + 9, top_offset + 1, 96 + N);
	osd_p->wr_char(left_offset + 10, top_offset + 1, 96 + O);

	osd_p->wr_char(left_offset + 0, top_offset + 2, 64 + E);
	osd_p->wr_char(left_offset + 1, top_offset + 2, 64 + C);
	osd_p->wr_char(left_offset + 2, top_offset + 2, 64 + E);
	osd_p->wr_char(left_offset + 3, top_offset + 2, 0);
	osd_p->wr_char(left_offset + 4, top_offset + 2, 48 + 4);
	osd_p->wr_char(left_offset + 5, top_offset + 2, 48 + 3);
	osd_p->wr_char(left_offset + 6, top_offset + 2, 48 + 0);
	osd_p->wr_char(left_offset + 7, top_offset + 2, 48 + 5);
}

void difficulty_screen_disp(OsdCore *osd_p) {
	osd_p->set_color(0x0f0, 0x001); // green/dark grey
	osd_p->bypass(0);
	osd_p->clr_screen();

	// Display Name, Course
	osd_p->wr_char(30 + 0, 10, 64 + T);
	osd_p->wr_char(30 + 1, 10, 64 + U);
	osd_p->wr_char(30 + 2, 10, 64 + R);
	osd_p->wr_char(30 + 3, 10, 64 + N);
	osd_p->wr_char(30 + 4, 10, 0);
	osd_p->wr_char(30 + 5, 10, 64 + P);
	osd_p->wr_char(30 + 6, 10, 64 + O);
	osd_p->wr_char(30 + 7, 10, 64 + T);
	osd_p->wr_char(30 + 8, 10, 64 + E);
	osd_p->wr_char(30 + 9, 10, 64 + N);
	osd_p->wr_char(30 + 10, 10, 64 + T);
	osd_p->wr_char(30 + 11, 10, 64 + I);
	osd_p->wr_char(30 + 12, 10, 64 + O);
	osd_p->wr_char(30 + 13, 10, 64 + M);
	osd_p->wr_char(30 + 14, 10, 64 + E);
	osd_p->wr_char(30 + 15, 10, 64 + T);
	osd_p->wr_char(30 + 16, 10, 64 + E);
	osd_p->wr_char(30 + 17, 10, 64 + R);
	osd_p->wr_char(30 + 18, 10, 0);
	osd_p->wr_char(30 + 19, 10, 64 + T);
	osd_p->wr_char(30 + 20, 10, 64 + O);

	osd_p->wr_char(29 + 0, 11, 64 + A);
	osd_p->wr_char(29 + 1, 11, 64 + D);
	osd_p->wr_char(29 + 2, 11, 64 + J);
	osd_p->wr_char(29 + 3, 11, 64 + U);
	osd_p->wr_char(29 + 4, 11, 64 + S);
	osd_p->wr_char(29 + 5, 11, 64 + T);
	osd_p->wr_char(29 + 6, 11, 0);
	osd_p->wr_char(29 + 7, 11, 64 + S);
	osd_p->wr_char(29 + 8, 11, 64 + P);
	osd_p->wr_char(29 + 9, 11, 64 + E);
	osd_p->wr_char(29 + 10, 11, 64 + E);
	osd_p->wr_char(29 + 11, 11, 64 + D);
	osd_p->wr_char(29 + 12, 11, 0);
	osd_p->wr_char(29 + 13, 11, 64 + D);
	osd_p->wr_char(29 + 14, 11, 64 + I);
	osd_p->wr_char(29 + 15, 11, 64 + F);
	osd_p->wr_char(29 + 16, 11, 64 + F);
	osd_p->wr_char(29 + 17, 11, 64 + I);
	osd_p->wr_char(29 + 18, 11, 64 + C);
	osd_p->wr_char(29 + 19, 11, 64 + U);
	osd_p->wr_char(29 + 20, 11, 64 + L);
	osd_p->wr_char(29 + 21, 11, 64 + T);
	osd_p->wr_char(29 + 22, 11, 64 + Y);

	osd_p->wr_char(31 + 0, 20, 64 + P);
	osd_p->wr_char(31 + 1, 20, 64 + R);
	osd_p->wr_char(31 + 2, 20, 64 + E);
	osd_p->wr_char(31 + 3, 20, 64 + S);
	osd_p->wr_char(31 + 4, 20, 64 + S);
	osd_p->wr_char(31 + 5, 20, 0);
	osd_p->wr_char(31 + 6, 20, 64 + B);
	osd_p->wr_char(31 + 7, 20, 64 + T);
	osd_p->wr_char(31 + 8, 20, 64 + N);
	osd_p->wr_char(31 + 9, 20, 64 + C);
	osd_p->wr_char(31 + 10, 20, 0);
	osd_p->wr_char(31 + 11, 20, 64 + T);
	osd_p->wr_char(31 + 12, 20, 64 + O);
	osd_p->wr_char(31 + 13, 20, 0);
	osd_p->wr_char(31 + 14, 20, 64 + S);
	osd_p->wr_char(31 + 15, 20, 64 + T);
	osd_p->wr_char(31 + 16, 20, 64 + A);
	osd_p->wr_char(31 + 17, 20, 64 + R);
	osd_p->wr_char(31 + 18, 20, 64 + T);
}

double difficulty_select_disp(OsdCore *osd_p, XadcCore *adc_p) {
	int k;
	double reading = 0;
	double volts = 0;
	int difficulty = 1;
	double delay = 0;

	for (k = 0; k < 4; k++) {
		reading = adc_p->read_adc_in(k);
		volts += reading;
	}

	if (volts <= 0.2) {
		difficulty = 1;
		delay = 2.0;
	}
	else if (volts <= 0.4) {
		difficulty = 2;
		delay = 1.75;
	}
	else if (volts <= 0.6) {
		difficulty = 3;
		delay = 1.50;
	}
	else if (volts <= 0.8) {
		difficulty = 4;
		delay = 1.25;
	}
	else {
		difficulty = 5;
		delay = 1.0;
	}

	osd_p->set_color(0x0f0, 0x001); // green/dark grey
	osd_p->bypass(0);
	osd_p->wr_char(39, 13, 48 + difficulty);

	return delay;
}

void ready_screen_disp(OsdCore *osd_p) {
	osd_p->set_color(0x0f0, 0x001); // green/dark grey
	osd_p->bypass(0);
	osd_p->clr_screen();

	// Display "GAME STARTS IN: "
	osd_p->wr_char(32 + 0, 10, 64 + G);
	osd_p->wr_char(32 + 1, 10, 64 + A);
	osd_p->wr_char(32 + 2, 10, 64 + M);
	osd_p->wr_char(32 + 3, 10, 64 + E);
	osd_p->wr_char(32 + 4, 10, 0);
	osd_p->wr_char(32 + 5, 10, 64 + S);
	osd_p->wr_char(32 + 6, 10, 64 + T);
	osd_p->wr_char(32 + 7, 10, 64 + A);
	osd_p->wr_char(32 + 8, 10, 64 + R);
	osd_p->wr_char(32 + 9, 10, 64 + T);
	osd_p->wr_char(32 + 10, 10, 64 + S);
	osd_p->wr_char(32 + 11, 10, 0);
	osd_p->wr_char(32 + 12, 10, 64 + I);
	osd_p->wr_char(32 + 13, 10, 64 + N);
	osd_p->wr_char(32 + 14, 10, 48 + 10);
}

bool ready_countdown_disp(OsdCore *osd_p, Ps2Core *ps2_p, SpriteCore *mouse_p, bool reset) {
	static int countdown = 6;
	static long start_time;
	const int xmax = 649;
	const int ymax = 479;
	static int x = 0;
	static int y = 0;
	int tmp_x;
	int tmp_y;
	int lbtn, rbtn, xmov, ymov;

	if (reset == true) {
		countdown = 6;
	}

	osd_p->wr_char(38, 13, 47 + countdown);

	start_time = now_ms();

	while ((now_ms() - start_time) < 1000) {
		if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
			tmp_x = x + xmov;
			tmp_y = y - ymov;

			if(0 <= tmp_x && tmp_x <= xmax) {
			   x = tmp_x;
			}

			if(0 <= tmp_y && tmp_y <= ymax) {
			   y = tmp_y;
			}

			mouse_p->move_xy(x, y);
		}
	}
	countdown--;

	if (countdown == 0) {
		return true;
	}
	else
	{
		return false;
	}
}

void play_screen_disp(OsdCore *osd_p) {
	osd_p->set_color(0x0f0, 0x001); // green/dark grey
	osd_p->bypass(0);
	osd_p->clr_screen();

	// Display "# of targets hit: 0/0"
	osd_p->wr_char(31 + 0, 24, 35);
	osd_p->wr_char(31 + 1, 24, 0);
	osd_p->wr_char(31 + 2, 24, 64 + O);
	osd_p->wr_char(31 + 3, 24, 64 + F);
	osd_p->wr_char(31 + 4, 24, 0);
	osd_p->wr_char(31 + 5, 24, 64 + T);
	osd_p->wr_char(31 + 6, 24, 64 + A);
	osd_p->wr_char(31 + 7, 24, 64 + R);
	osd_p->wr_char(31 + 8, 24, 64 + G);
	osd_p->wr_char(31 + 9, 24, 64 + E);
	osd_p->wr_char(31 + 10, 24, 64 + T);
	osd_p->wr_char(31 + 11, 24, 64 + S);
	osd_p->wr_char(31 + 12, 24, 0);
	osd_p->wr_char(31 + 13, 24, 64 + H);
	osd_p->wr_char(31 + 14, 24, 64 + I);
	osd_p->wr_char(31 + 15, 24, 64 + T);
	osd_p->wr_char(31 + 16, 24, 48 + 10);
	osd_p->wr_char(31 + 17, 24, 0);
	osd_p->wr_char(31 + 18, 24, 48 + 0);
	osd_p->wr_char(31 + 19, 24, 47);
	osd_p->wr_char(31 + 20, 24, 48 + 0);

	// Display "AVERAGE REACTION TIME: 0.00S"
	osd_p->wr_char(28 + 0, 25, 64 + A);
	osd_p->wr_char(28 + 1, 25, 64 + V);
	osd_p->wr_char(28 + 2, 25, 64 + E);
	osd_p->wr_char(28 + 3, 25, 64 + R);
	osd_p->wr_char(28 + 4, 25, 64 + A);
	osd_p->wr_char(28 + 5, 25, 64 + G);
	osd_p->wr_char(28 + 6, 25, 64 + E);
	osd_p->wr_char(28 + 7, 25, 0);
	osd_p->wr_char(28 + 8, 25, 64 + R);
	osd_p->wr_char(28 + 9, 25, 64 + E);
	osd_p->wr_char(28 + 10, 25, 64 + A);
	osd_p->wr_char(28 + 11, 25, 64 + C);
	osd_p->wr_char(28 + 12, 25, 64 + T);
	osd_p->wr_char(28 + 13, 25, 64 + I);
	osd_p->wr_char(28 + 14, 25, 64 + O);
	osd_p->wr_char(28 + 15, 25, 64 + N);
	osd_p->wr_char(28 + 16, 25, 0);
	osd_p->wr_char(28 + 17, 25, 64 + T);
	osd_p->wr_char(28 + 18, 25, 64 + I);
	osd_p->wr_char(28 + 19, 25, 64 + M);
	osd_p->wr_char(28 + 20, 25, 64 + E);
	osd_p->wr_char(28 + 21, 25, 48 + 10);
	osd_p->wr_char(28 + 22, 25, 0);
	osd_p->wr_char(28 + 23, 25, 48 + 0);
	osd_p->wr_char(28 + 24, 25, 46);
	osd_p->wr_char(28 + 25, 25, 48 + 0);
	osd_p->wr_char(28 + 26, 25, 48 + 0);
	osd_p->wr_char(28 + 27, 25, 96 + S);
}

double target_hit(SpriteCore *ghost_p, SpriteCore *mouse_p, Ps2Core *ps2_p, double delay) {
	const int xmax = 649;
	const int ymax = 479;
	static int mouse_x = 0;
	static int mouse_y = 0;
	int tmp_mouse_x, tmp_mouse_y;
	int lbtn, rbtn, xmov, ymov;
	int ghost_x = rand() % 624;		// make sure entire ghost is on the screen
	int ghost_y = rand() % 464;
	bool hit = false;
	double reaction_speed = 0;
	long start_time = 0;

	ghost_p->bypass(0);
	ghost_p->move_xy(ghost_x, ghost_y);
	start_time = now_ms();

	while (((now_ms() - start_time) <= delay) and (hit == false)) {
		if (ps2_p->get_mouse_activity(&lbtn, &rbtn, &xmov, &ymov)) {
			tmp_mouse_x = mouse_x + xmov;
			tmp_mouse_y = mouse_y - ymov;

			if(tmp_mouse_x >= 0 && tmp_mouse_x <= xmax) {
				mouse_x = tmp_mouse_x;
			}

			if(tmp_mouse_y >= 0 && tmp_mouse_y <= ymax) {
				mouse_y = tmp_mouse_y;
			}

			mouse_p->move_xy(mouse_x, mouse_y);

			if ((lbtn == 1) and ((mouse_x >= ghost_x-15) and (mouse_x <= ghost_x+5)) and ((mouse_y >= ghost_y-13) and (mouse_y <= ghost_y))) {
				hit = true;
				reaction_speed = now_ms() - start_time;
				sleep_ms(75);
				return reaction_speed;
			}
		}
	}

	return reaction_speed;
}

void avg_speed_disp(OsdCore *osd_p, double avg, int hits, int count) {
	int avg_ones = ((int)avg) / 1000;
	int avg_tenths = (((int)avg) % 1000)/100;
	int avg_hundredths = (((int)avg) % 100)/10;

	// Display average reaction speed
	osd_p->wr_char(28 + 23, 25, 48 + avg_ones);
	osd_p->wr_char(28 + 25, 25, 48 + avg_tenths);
	osd_p->wr_char(28 + 26, 25, 48 + avg_hundredths);
	osd_p->wr_char(28 + 27, 25, 96 + S);

	// Display # of targets hit so far
	if (count > 9) {
		if (hits > 9) {
			osd_p->wr_char(31 + 18, 24, 48 + hits/10);
			osd_p->wr_char(31 + 19, 24, 48 + hits%10);
			osd_p->wr_char(31 + 20, 24, 47);
			osd_p->wr_char(31 + 21, 24, 48 + count/10);
			osd_p->wr_char(31 + 22, 24, 48 + count%10);
		}
		else {
			osd_p->wr_char(31 + 18, 24, 48 + hits%10);
			osd_p->wr_char(31 + 19, 24, 47);
			osd_p->wr_char(31 + 20, 24, 48 + count/10);
			osd_p->wr_char(31 + 21, 24, 48 + count%10);
		}
	}
	else {
		osd_p->wr_char(31 + 18, 24, 48 + hits%10);
		osd_p->wr_char(31 + 19, 24, 47);
		osd_p->wr_char(31 + 20, 24, 48 + count%10);
	}
}

void end_screen_disp(OsdCore *osd_p, int hits, double avg) {
	int avg_ones = ((int)avg) / 1000;
	int avg_tenths = (((int)avg) % 1000)/100;
	int avg_hundredths = (((int)avg) % 100)/10;

	// Skill Level:
	// [skill level]
	//
	// You hit xx/25 targets
	// at an average speed of [x.xx] seconds
	//
	// Press BTNC to exit

	osd_p->set_color(0x0f0, 0x001); // green/dark grey
	osd_p->bypass(0);
	osd_p->clr_screen();

	if (hits <= 5) {
		// Novice
		osd_p->wr_char(36 + 0, 11, 64 + N);
		osd_p->wr_char(36 + 1, 11, 64 + O);
		osd_p->wr_char(36 + 2, 11, 64 + V);
		osd_p->wr_char(36 + 3, 11, 64 + I);
		osd_p->wr_char(36 + 4, 11, 64 + C);
		osd_p->wr_char(36 + 5, 11, 64 + E);
	}
	else if (hits <= 10) {
		// Amateur
		osd_p->wr_char(35 + 0, 11, 64 + A);
		osd_p->wr_char(35 + 1, 11, 64 + M);
		osd_p->wr_char(35 + 2, 11, 64 + A);
		osd_p->wr_char(35 + 3, 11, 64 + T);
		osd_p->wr_char(35 + 4, 11, 64 + E);
		osd_p->wr_char(35 + 5, 11, 64 + U);
		osd_p->wr_char(35 + 6, 11, 64 + R);
	}
	else if (hits <= 15) {
		// Intermediate
		osd_p->wr_char(33 + 0, 11, 64 + I);
		osd_p->wr_char(33 + 1, 11, 64 + N);
		osd_p->wr_char(33 + 2, 11, 64 + T);
		osd_p->wr_char(33 + 3, 11, 64 + E);
		osd_p->wr_char(33 + 4, 11, 64 + R);
		osd_p->wr_char(33 + 5, 11, 64 + M);
		osd_p->wr_char(33 + 6, 11, 64 + E);
		osd_p->wr_char(33 + 7, 11, 64 + D);
		osd_p->wr_char(33 + 8, 11, 64 + I);
		osd_p->wr_char(33 + 9, 11, 64 + A);
		osd_p->wr_char(33 + 10, 11, 64 + T);
		osd_p->wr_char(33 + 11, 11, 64 + E);
	}
	else if (hits <= 20) {
		// Expert
		osd_p->wr_char(36 + 0, 11, 64 + E);
		osd_p->wr_char(36 + 1, 11, 64 + X);
		osd_p->wr_char(36 + 2, 11, 64 + P);
		osd_p->wr_char(36 + 3, 11, 64 + E);
		osd_p->wr_char(36 + 4, 11, 64 + R);
		osd_p->wr_char(36 + 5, 11, 64 + T);
	}
	else if (hits <= 24){
		// Master
		osd_p->wr_char(36 + 0, 11, 64 + M);
		osd_p->wr_char(36 + 1, 11, 64 + A);
		osd_p->wr_char(36 + 2, 11, 64 + S);
		osd_p->wr_char(36 + 3, 11, 64 + T);
		osd_p->wr_char(36 + 4, 11, 64 + E);
		osd_p->wr_char(36 + 5, 11, 64 + R);
	}
	else {
		// Grand Master
		osd_p->wr_char(33 + 0, 11, 64 + G);
		osd_p->wr_char(33 + 1, 11, 64 + R);
		osd_p->wr_char(33 + 2, 11, 64 + A);
		osd_p->wr_char(33 + 3, 11, 64 + N);
		osd_p->wr_char(33 + 4, 11, 64 + D);
		osd_p->wr_char(33 + 5, 11, 0);
		osd_p->wr_char(33 + 6, 11, 64 + M);
		osd_p->wr_char(33 + 7, 11, 64 + A);
		osd_p->wr_char(33 + 8, 11, 64 + S);
		osd_p->wr_char(33 + 9, 11, 64 + T);
		osd_p->wr_char(33 + 10, 11, 64 + E);
		osd_p->wr_char(33 + 11, 11, 64 + R);
	}

	// "Skill Level:
	osd_p->wr_char(33 + 0, 10, 64 + S);
	osd_p->wr_char(33 + 1, 10, 64 + K);
	osd_p->wr_char(33 + 2, 10, 64 + I);
	osd_p->wr_char(33 + 3, 10, 64 + L);
	osd_p->wr_char(33 + 4, 10, 64 + L);
	osd_p->wr_char(33 + 5, 10, 0);
	osd_p->wr_char(33 + 6, 10, 64 + L);
	osd_p->wr_char(33 + 7, 10, 64 + E);
	osd_p->wr_char(33 + 8, 10, 64 + V);
	osd_p->wr_char(33 + 9, 10, 64 + E);
	osd_p->wr_char(33 + 10, 10, 64 + L);
	osd_p->wr_char(33 + 11, 10, 48 + 10);

	// "You hit xx/25 targets"
	osd_p->wr_char(28 + 0, 15, 64 + Y);
	osd_p->wr_char(28 + 1, 15, 64 + O);
	osd_p->wr_char(28 + 2, 15, 64 + U);
	osd_p->wr_char(28 + 3, 15, 0);
	osd_p->wr_char(28 + 4, 15, 64 + H);
	osd_p->wr_char(28 + 5, 15, 64 + I);
	osd_p->wr_char(28 + 6, 15, 64 + T);
	osd_p->wr_char(28 + 7, 15, 0);
	osd_p->wr_char(28 + 8, 15, 48 + hits/10);
	osd_p->wr_char(28 + 9, 15, 48 + hits%10);
	osd_p->wr_char(28 + 10, 15, 47);
	osd_p->wr_char(28 + 11, 15, 48 + 2);
	osd_p->wr_char(28 + 12, 15, 48 + 5);
	osd_p->wr_char(28 + 13, 15, 0);
	osd_p->wr_char(28 + 14, 15, 64 + T);
	osd_p->wr_char(28 + 15, 15, 64 + A);
	osd_p->wr_char(28 + 16, 15, 64 + R);
	osd_p->wr_char(28 + 17, 15, 64 + G);
	osd_p->wr_char(28 + 18, 15, 64 + E);
	osd_p->wr_char(28 + 19, 15, 64 + T);
	osd_p->wr_char(28 + 20, 15, 64 + S);

	// "at an average speed of x.xx seconds"
	osd_p->wr_char(21 + 1, 16, 64 + A);
	osd_p->wr_char(21 + 2, 16, 64 + T);
	osd_p->wr_char(21 + 3, 16, 0);
	osd_p->wr_char(21 + 4, 16, 64 + A);
	osd_p->wr_char(21 + 5, 16, 64 + N);
	osd_p->wr_char(21 + 6, 16, 0);
	osd_p->wr_char(21 + 7, 16, 64 + A);
	osd_p->wr_char(21 + 8, 16, 64 + V);
	osd_p->wr_char(21 + 9, 16, 64 + E);
	osd_p->wr_char(21 + 10, 16, 64 + R);
	osd_p->wr_char(21 + 11, 16, 64 + A);
	osd_p->wr_char(21 + 12, 16, 64 + G);
	osd_p->wr_char(21 + 13, 16, 64 + E);
	osd_p->wr_char(21 + 14, 16, 0);
	osd_p->wr_char(21 + 15, 16, 64 + S);
	osd_p->wr_char(21 + 16, 16, 64 + P);
	osd_p->wr_char(21 + 17, 16, 64 + E);
	osd_p->wr_char(21 + 18, 16, 64 + E);
	osd_p->wr_char(21 + 19, 16, 64 + D);
	osd_p->wr_char(21 + 20, 16, 0);
	osd_p->wr_char(21 + 21, 16, 64 + O);
	osd_p->wr_char(21 + 22, 16, 64 + F);
	osd_p->wr_char(21 + 23, 16, 0);
	osd_p->wr_char(21 + 24, 16, 48 + avg_ones);
	osd_p->wr_char(21 + 25, 16, 46);
	osd_p->wr_char(21 + 26, 16, 48 + avg_tenths);
	osd_p->wr_char(21 + 27, 16, 48 + avg_hundredths);
	osd_p->wr_char(21 + 28, 16, 0);
	osd_p->wr_char(21 + 29, 16, 64 + S);
	osd_p->wr_char(21 + 30, 16, 64 + E);
	osd_p->wr_char(21 + 31, 16, 64 + C);
	osd_p->wr_char(21 + 32, 16, 64 + O);
	osd_p->wr_char(21 + 33, 16, 64 + N);
	osd_p->wr_char(21 + 34, 16, 64 + D);
	osd_p->wr_char(21 + 35, 16, 64 + S);

	// Display prompt for exit button
	osd_p->wr_char(31 + 0, 20, 64 + P);
	osd_p->wr_char(31 + 1, 20, 64 + R);
	osd_p->wr_char(31 + 2, 20, 64 + E);
	osd_p->wr_char(31 + 3, 20, 64 + S);
	osd_p->wr_char(31 + 4, 20, 64 + S);
	osd_p->wr_char(31 + 5, 20, 0);
	osd_p->wr_char(31 + 6, 20, 64 + B);
	osd_p->wr_char(31 + 7, 20, 64 + T);
	osd_p->wr_char(31 + 8, 20, 64 + N);
	osd_p->wr_char(31 + 9, 20, 64 + C);
	osd_p->wr_char(31 + 10, 20, 0);
	osd_p->wr_char(31 + 11, 20, 64 + T);
	osd_p->wr_char(31 + 12, 20, 64 + O);
	osd_p->wr_char(31 + 13, 20, 0);
	osd_p->wr_char(31 + 14, 20, 64 + E);
	osd_p->wr_char(31 + 15, 20, 64 + X);
	osd_p->wr_char(31 + 16, 20, 64 + I);
	osd_p->wr_char(31 + 17, 20, 64 + T);
}

bool btn_check(DebounceCore *btn_p, int button) {
	bool btn_click = false;
	double btn = btn_p->read_db(button);
	if (btn) {
		btn_click = true;
	}
	return btn_click;
}

void frame_check(FrameCore *frame_p) {
   frame_p->bypass(0);
   frame_p->clr_screen(0x001);  // dark grey background
}

// external core instantiation
GpiCore sw(get_slot_addr(BRIDGE_BASE, S3_SW));
XadcCore adc(get_slot_addr(BRIDGE_BASE, S5_XDAC));
DebounceCore btn(get_slot_addr(BRIDGE_BASE, S7_BTN));
FrameCore frame(FRAME_BASE);
SpriteCore ghost(get_sprite_addr(BRIDGE_BASE, V3_GHOST), 1024);
SpriteCore mouse(get_sprite_addr(BRIDGE_BASE, V1_MOUSE), 1024);
OsdCore osd(get_sprite_addr(BRIDGE_BASE, V2_OSD));
Ps2Core ps2(get_slot_addr(BRIDGE_BASE, S11_PS2));

int main() {
	bool main_screen = true;
	bool difficulty_screen = false;
	bool ready_screen = false;
	bool play_screen = false;
	bool end_screen = false;

	ps2.init();
	frame_check(&frame);
	mouse.bypass(1);
	ghost.bypass(1);
	ghost.wr_ctrl(0x01);

	while (1) {
		int osd_set = false;	// on-screen-display text has not been set
		double delay = 1.0;
		// Main Screen (Screen 1)
		while (main_screen) {
			// set osd text for main screen once
			if (osd_set == false) {
				main_screen_disp(&osd);
				osd_set = true;
			}

			// display animation
			main_screen_animation(&ghost, &mouse);

			// check for start button
			bool start_1 = btn_check(&btn, btn_c);
			if (start_1 == true) {
				main_screen = false;
				difficulty_screen = true;	// move to second screen
				osd_set = false;			// reset "osd text set" flag
				ghost.bypass(1);			// hide ghost
				mouse.bypass(1);			// hide mouse
				sleep_ms(250);				// debounce
			}
		}

		// Difficulty Screen (Screen 2)
		while (difficulty_screen) {
			// set osd text for difficulty screen once
			if (osd_set == false) {
				difficulty_screen_disp(&osd);
				osd_set = true;
			}

			// check for start button
			bool start_2 = btn_check(&btn, btn_c);
			if (start_2 == true) {
				difficulty_screen = false;
				ready_screen = true;		// move to third screen
				osd_set = false;			// reset "osd text set" flag
				sleep_ms(250);				// debounce
			}
			else {
				// display difficulty controlled by potentiometer
				delay = 1000*difficulty_select_disp(&osd, &adc);
			}
		}

		bool reset_count = true;
		// Ready Screen (Screen 3)
		while (ready_screen) {
			// set osd text for ready screen once
			if (osd_set == false) {
				ready_screen_disp(&osd);
				mouse.bypass(0);
				mouse.move_xy(319, 239);
				osd_set = true;
			}
			else {
				bool start_3 = ready_countdown_disp(&osd, &ps2, &mouse, reset_count);
				reset_count = false;
				if (start_3 == true) {
					ready_screen = false;
					play_screen = true;		// move to fourth screen
					osd_set = false;		// reset "osd text set" flag
				}
			}
		}

		// Play Screen (Screen 4)
		int hits = 0;
		double sum = 0;
		double avg = 0;
		double reaction_time = 0;

		while (play_screen) {
			if (osd_set == false) {
				play_screen_disp(&osd);
				osd_set = true;
			}
			else {
				mouse.bypass(0);
				for (int n = 1; n <= 25; n++) {
					reaction_time = target_hit(&ghost, &mouse, &ps2, delay);
					if (reaction_time != 0) {
						hits++;
						sum = sum + reaction_time;
						avg = sum/hits;
					}

					avg_speed_disp(&osd, avg, hits, n);
					ghost.bypass(1);
					sleep_ms(delay);
				}
				play_screen = false;
				end_screen = true;		// move to fifth screen
				osd_set = false;		// reset "osd text set" flag
			}
		}

		// End Screen (Screen 5)
		while (end_screen) {
			bool exit = btn_check(&btn, btn_c);
			if (osd_set == false) {
				end_screen_disp(&osd, hits, avg);
				osd_set = true;
			}
			else if (exit == true) {
				end_screen = false;
				main_screen = true;
				osd_set = false;
				sleep_ms(250);
			}
		}
	}
}
