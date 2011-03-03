#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <cc3.h>
#include <cc3_ilp.h>
#include <jpeglib.h>

#define KEY_ESC 27

static struct jpeg_compress_struct cinfo;
static struct jpeg_error_mgr jerr;
uint8_t *row;

static void CaptureCurrentJPEG(FILE *f);
static void InitJPEG(void);
static void DestroyJPEG(void);

/***********
Programm to test the saving of images to the SD card
***********/

int main (void)
{
	//uint32_t start_time, end_time;
	uint32_t val;
	char c;
	FILE *f;

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
	bool auto_balance = false, auto_exposure = false;
	int high_resolution = CC3_CAMERA_RESOLUTION_LOW;
	printf("High Resolution? (y or n)\n");
	c = getchar();
	if (c== 'y' || c == 'Y')
		high_resolution = CC3_CAMERA_RESOLUTION_HIGH;
	
	printf("Autobalance? (y or n)\n");
	c = getchar();
	if (c== 'y' || c == 'Y')
		auto_balance = true;
	
	printf("Auto Exposure? (y or n)\n");
	c = getchar();
	if (c== 'y' || c == 'Y')
		auto_exposure = true;

	cc3_camera_set_colorspace (CC3_COLORSPACE_RGB);
	cc3_camera_set_resolution (high_resolution);
	cc3_camera_set_auto_white_balance (auto_balance);
	cc3_camera_set_auto_exposure (auto_exposure);

	cc3_pixbuf_load ();
	InitJPEG();

	char heading[32];
	printf("Heading?\n");
	gets(heading);

	// Wait command in ms
	cc3_timer_wait_ms (1000);
	cc3_led_set_state (0, true);

	printf ("Type y to test MMC card, type n if you do not have the card.\n");
	c = getchar ();
	if (c != 'y' && c != 'Y') 
	{
		printf("QUIT PROGRAM...\n");
		DestroyJPEG();
		return 0;
	}

	printf("Press ESC to quit\n");
	// Wait for the button to be pushed
	// Read button
	bool exit_button = false;
	int noFrame = 0;
	char filename[16];
	while (!exit_button)
	{
		//printf ("Push button on camera back to take a picture\n");
		//while (!cc3_button_get_state ());
		//cc3_led_set_state (1, true);

		// Timer
		//start_time = cc3_timer_get_current_ms ();
		//printf ("It took you %dms to press the button\n", cc3_timer_get_current_ms () - start_time);

		// Take a picture
		cc3_pixbuf_load ();

		// Save the image to the SD card
		sprintf(filename, "c:/%s_n%d.jpg", heading, noFrame);
		f = fopen(filename, "w");
		if (NULL == f)
		{
			printf("Error while opening the filename %s\n", filename);
			exit_button = true;
			continue;
		}

		//SaveImage(f);
		CaptureCurrentJPEG(f);
		fclose(f);
		noFrame++;
		//end_time = cc3_timer_get_current_ms();

		printf("Frame successfully saved in %s\n", filename);
		c = getchar();
		if (KEY_ESC == c)
		{
			exit_button = true;
			continue;
		}
	}

    // Non-blocking serial routine
    //if (!cc3_uart_has_data (0))
    //  break;
	DestroyJPEG();
	printf("QUIT PROGRAM\n\n");
	return 0;
}

void InitJPEG(void) 
{
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	// parameters for jpeg image
	cinfo.image_width = cc3_g_pixbuf_frame.width;
	cinfo.image_height = cc3_g_pixbuf_frame.height;
	printf( "Wwidth = %d Height = %d\n", cinfo.image_width, cinfo.image_height );
	cinfo.input_components = 3;
	// cinfo.in_color_space = JCS_YCbCr;
	cinfo.in_color_space = JCS_RGB;

	// set image quality, etc.
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 80, true);

	// allocate memory for 1 row
	row = cc3_malloc_rows(1);
	if(NULL == row) 
		printf( "Out of memory!\n" );
}

void CaptureCurrentJPEG(FILE *f) 
{
	JSAMPROW row_pointer[1];
	row_pointer[0] = row;

	// Output is file
	jpeg_stdio_dest(&cinfo, f);

	// Read and compress
	jpeg_start_compress(&cinfo, TRUE);
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		cc3_pixbuf_read_rows(row, 1);
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
  
	// Finish
	jpeg_finish_compress(&cinfo);
}



void DestroyJPEG(void) 
{
	jpeg_destroy_compress(&cinfo);
	free(row);
}
