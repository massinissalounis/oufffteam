#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cc3.h"

// Duration of the initial phase of matches during when the grab period is low
#define INIT_PHASE_DURATION			120000
#define INIT_PHASE_GRAB_PERIOD		0//1000
#define NORMAL_PHASE_GRAB_PERIOD	0//200

void capture_ppm(FILE* fp);

int main(void) 
{
	uint32_t init_time, current_time;
	uint32_t grab_period;
	char filename[16];
	FILE *f;

	grab_period = INIT_PHASE_GRAB_PERIOD; // At first grab every second

	cc3_uart_init (0,
		 CC3_UART_RATE_115200,
		 CC3_UART_MODE_8N1,
		 CC3_UART_BINMODE_TEXT);

	cc3_camera_init ();
	// use MMC
	cc3_filesystem_init();

	cc3_camera_set_resolution(CC3_CAMERA_RESOLUTION_HIGH);
	cc3_pixbuf_frame_set_subsample (CC3_SUBSAMPLE_NEAREST, 2, 2);

	init_time = cc3_timer_get_current_ms();

	uint32_t i = 0;
	while(true) 
	{
		i++;
		printf("%d\n", i);
		current_time = cc3_timer_get_current_ms() - init_time;
		snprintf(filename, 16, "c:/%.5d.ppm", current_time);
		f = fopen(filename, "w");
		capture_ppm(f);
		fclose(f);
		if (current_time > INIT_PHASE_DURATION)
			grab_period = NORMAL_PHASE_GRAB_PERIOD;
		cc3_timer_wait_ms(grab_period);
	 }

	return 0;
}

void capture_ppm(FILE *f)
{
	uint32_t x, y;
	uint32_t size_x, size_y;

	uint32_t time, time2;
	int write_time;

	cc3_pixbuf_load ();
	uint8_t *row = cc3_malloc_rows(1);

	size_x = cc3_g_pixbuf_frame.width;
	size_y = cc3_g_pixbuf_frame.height;

	fprintf(f,"P6\n%d %d\n255\n",size_x, size_y);

	time = cc3_timer_get_current_ms();
	for (y = 0; y < size_y; y++) 
	{
		cc3_pixbuf_read_rows(row, 1);
		for (x = 0; x < size_x * 3U; x++) 
		{
			uint8_t p = row[x];
			if (fputc(p, f) == EOF) 
			{
				perror("fputc failed");
			}
		}
		fprintf(stderr, ".");
		fflush(stderr);
	}
	time2 = cc3_timer_get_current_ms();
	write_time = time2 - time;

	free(row);

	fprintf(stderr, "\nwrite_time  %10d\n", write_time);
}
