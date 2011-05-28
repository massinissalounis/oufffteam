#include <stdio.h>
#include <stdlib.h>

#include "cc3.h"
#include "jpeglib.h"
#include "Parameters.h"

static struct jpeg_compress_struct cinfo;
static struct jpeg_error_mgr jerr;
uint8_t *row;

static void capture_current_jpeg(FILE *f);
static int init_jpeg(void);
static void destroy_jpeg(void);

int main(void)
{
	int i, maxNbImages;
	FILE *f;
	char filename[16];
	uint32_t current_time, start_time;

	// Compute the maximum number of images the card can grab

	// Initialisation
	cc3_uart_init (0, 
		 CC3_UART_RATE_115200,
		 CC3_UART_MODE_8N1,
		 CC3_UART_BINMODE_TEXT);

	cc3_camera_init ();
	cc3_filesystem_init();

	cc3_camera_set_resolution(RESOLUTION_TYPE);

	// Init pixbuf with width and height
	cc3_pixbuf_load();

	// Init jpeg
	if (0 != init_jpeg())
	{
		printf("Error: not enough memory!");
		return -1;
	}

	i = 0;
	start_time = cc3_timer_get_current_ms();
	while(true) 
	{
		cc3_timer_wait_ms(GRAB_PERIOD);
		current_time = cc3_timer_get_current_ms();
		snprintf(filename, 16, "c:/%.5d.jpg", current_time - start_time);
		// Check if files exist, if they do then skip over them 
		do 
		{ 
			f = fopen(filename, "r");
    		if(NULL != f) 
			{ 
				i++; 
				snprintf(filename, 16, "c:/%.5d_%1d.jpg", current_time - start_time, i);
				fclose(f);
			}
		} while(NULL != f && i < 5);

		// Print file that you are going to write to stderr
		//fprintf(stderr,"%s\r\n", filename);
		f = fopen(filename, "w");
		if(NULL == f || i > 5)
		{
			//printf( "Error: Can't open file\r\n" );
			return 0;
		}
		capture_current_jpeg(f);
		fclose(f);
	}

	destroy_jpeg();
	return 0;
}

int init_jpeg(void) 
{
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  // Parameters for jpeg image
  cinfo.image_width = cc3_g_pixbuf_frame.width;
  cinfo.image_height = cc3_g_pixbuf_frame.height;
  //printf( "image width=%d image height=%d\n", cinfo.image_width, cinfo.image_height );
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  // Set image quality, etc.
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 80, true);

  // Allocate memory for 1 row
  row = cc3_malloc_rows(1);
  if(row == NULL) 
  {
	  printf( "Out of memory!\n" );
	  return -1;
  }
  return 0;
}

void capture_current_jpeg(FILE *f) 
{
  JSAMPROW row_pointer[1];
  row_pointer[0] = row;

  // Output is file
  jpeg_stdio_dest(&cinfo, f);

  // Capture a frame to the FIFO
  cc3_pixbuf_load();

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

void destroy_jpeg(void) 
{
  jpeg_destroy_compress(&cinfo);
  free(row);
}
