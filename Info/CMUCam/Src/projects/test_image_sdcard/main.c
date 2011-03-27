#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cc3.h>
#include <cc3_hsv.h>
#include <cc3_ilp.h>
#include <cc3_histogram.h>
#include <cc3_img_writer.h>

#define KEY_ESC 27

uint8_t *row;
cc3_image_t img;

void GetImage(cc3_image_t* img2Store);
void ImageProcessing();
void Thresholding(uint8_t *row, uint8_t *processedRow);
void GetHistogram (cc3_histogram_pkt_t *h_pkt);

/***********
Programm to test the saving of images to the SD card
***********/

int main (void)
{
	uint32_t grab_time;
	uint32_t val;
	char c;
	FILE *f;
	char heading[16];
	row = cc3_malloc_rows(1);
	if (row == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}

	/*********
	INITIALISATION 
	**********/
	// init filesystem driver
	cc3_filesystem_init ();

	// configure uart
	cc3_uart_init (0, CC3_UART_RATE_115200, CC3_UART_MODE_8N1, CC3_UART_BINMODE_TEXT);
	// Make it so that stdout and stdin are not buffered
	val = setvbuf (stdout, NULL, _IONBF, 0);
	val = setvbuf (stdin, NULL, _IONBF, 0);

	cc3_camera_init ();

	printf ("Test on saving images...\n");
	printf("BEGIN...\n");

	/***********
	CAMERA PROPERTIES
	***********/
	bool auto_balance = true, auto_exposure = true;
	cc3_camera_resolution_t resolution = CC3_CAMERA_RESOLUTION_LOW;
	//printf("High Resolution? (y or n)\n");
	//c = getchar();
	//if (c== 'y' || c == 'Y')
	//	resolution = CC3_CAMERA_RESOLUTION_HIGH;
	//printf("Autobalance? (y or n)\n");
	//c = getchar();
	//if (c== 'y' || c == 'Y')
	//	auto_balance = true;
	//
	//printf("Auto Exposure? (y or n)\n");
	//c = getchar();
	//if (c== 'y' || c == 'Y')
	//	auto_exposure = true;

	cc3_camera_set_colorspace (CC3_COLORSPACE_RGB);
	cc3_camera_set_resolution (resolution);
	cc3_camera_set_auto_white_balance (auto_balance);
	cc3_camera_set_auto_exposure (auto_exposure);
	cc3_pixbuf_frame_set_subsample (CC3_SUBSAMPLE_NEAREST, 2, 2);

	cc3_pixbuf_load ();

	img.channels = 3;
	img.width = cc3_g_pixbuf_frame.width;
	img.height = cc3_g_pixbuf_frame.height;
	img.pix = cc3_malloc_rows(cc3_g_pixbuf_frame.height);
	if (img.pix == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}

	// Wait command in ms
	cc3_timer_wait_ms (1000);
	cc3_led_set_state (0, true);

	printf("Heading?\n");
	gets(heading);

	printf("Press ESC to quit\n");
	// Wait for the button to be pushed
	// Read button
	bool exit_button = false;
	int noFrame = 0;
	char filename[64];
	while (!exit_button)
	{
		// Timer
		grab_time = cc3_timer_get_current_ms();

		// Take a picture
		cc3_pixbuf_load ();
		GetImage(&img);

		// Save the image to the SD card
		sprintf(filename, "c:/%s_%d.ppm", heading, grab_time);
		printf("MAIN:: Filename %s\n", filename);
		/*f = fopen(filename, "w");
		if (NULL == f)
		{
			printf("MAIN:: Error while opening the file\n");
			exit_button = true;
			continue;
		}*/

		//ImageProcessing();
		cc3_ppm_img_write(&img, filename);
		//fclose(f);
		noFrame++;

		//printf("MAIN:: Frame successfully saved\n");
		c = getchar();
		if (KEY_ESC == c)
		{
			exit_button = true;
			continue;
		}
	}

	free(img.pix);   
	free(row);

	printf("QUIT PROGRAM\n\n");
	return 0;
}

void GetImage(cc3_image_t *img2Store)
{
	printf("GETIMAGE:: Beginning\n");
	cc3_pixbuf_read_rows(img2Store->pix, cc3_g_pixbuf_frame.height);
	printf("GETIMAGE:: End\n");
}

void ImageProcessing()
{
	int32_t start_time, end_time;
	cc3_histogram_pkt_t imHist;

	for (uint32_t y = 0; y < cc3_g_pixbuf_frame.height; y++) 
	{
		cc3_pixbuf_read_rows(row, 1);
		Thresholding(row, &img.pix[y]);
	}

	imHist.channel = CC3_CHANNEL_HUE;
	imHist.bins = 180;
	imHist.hist = malloc(imHist.bins * sizeof (uint32_t));

	start_time = cc3_timer_get_current_ms();
	GetHistogram(&imHist);
	end_time = cc3_timer_get_current_ms();

	printf("Total time for Histogram %d\n", end_time - start_time);

	// Print the histogram out on the screen
    printf ("hist: ");
    for (uint8_t i = 0; i < imHist.bins; i++)
      printf ("%d ", imHist.hist[i]);
    printf ("\n");

	free(imHist.hist);
}

void GetHistogram(cc3_histogram_pkt_t *h_pkt)
{
	//cc3_pixbuf_rewind();
	//if (cc3_histogram_scanline_start(h_pkt) != 0) 
	//{
	//	while (cc3_pixbuf_read_rows(img.pix, 1)) 
	//		cc3_histogram_scanline(&img, h_pkt);
	//}
	//cc3_histogram_scanline_finish(h_pkt);
	//free (img.pix);
	//return;
}

void Thresholding(uint8_t *initRow, uint8_t *processedRow)
{
	uint8_t *HSVrow = cc3_malloc_rows(1);;
	*HSVrow = *initRow;
	cc3_rgb2hsv_row(HSVrow, cc3_g_pixbuf_frame.width); 
	for (uint32_t x = 0; x < cc3_g_pixbuf_frame.width; x++)
		if (HSVrow[x] > 50 && HSVrow[x] < 70)
			processedRow[x] = 1;
		else
			processedRow = 0;
	free(HSVrow);
}
