/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This file is serialConfig, a C program that sets your serial  *
 * port to 115,200 baud 8n1                                      *
 * Contact cmucam@cs.cmu.edu, or see                             *
 * http://www.cs.cmu.edu/~cmucam for more information.           *
 *                                                               *
 * Copyright 2001 Anthony Rowe                                   *
 *                                                               *
 * This program is free software; you can redistribute it and/or *
 * modify it under the terms of the GNU General Public License   *
 * as published by the Free Software Foundation - version 2.     *
 *                                                               *
 * This program is distributed in the hope that it will be       *
 * useful, but WITHOUT ANY WARRANTY; without even the implied    *
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       *
 * PURPOSE.  See the GNU General Public License in file COPYING  *
 * for more details.                                             *
 *                                                               *
 * You should have received a copy of the GNU General Public     *
 * License along with this program; if not, write to the Free    *
 * Software Foundation, Inc., 59 Temple Place - Suite 330,       *
 * Boston, MA 02111, USA.                                        *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <sys/signal.h>


int main(int argc, char *argv[]) {
  struct termios oldtio, newtio;
  struct sigaction saio;
  int s_port;
  char port_name[32];
  // Serial Setup
  
if(argc<=1) 
	{
	printf("No command line port entered, using default\n" );
	strcpy(port_name,"/dev/ttyS0" );
	s_port=open(port_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
	}
     else
	{
	strcpy(port_name,argv[1]);
	s_port=open(port_name,O_RDWR | O_NOCTTY | O_NONBLOCK);	
	}
  if (s_port<0) {
    printf("error opening serial port\n");
    exit(-1);
  }


  tcgetattr(s_port, &oldtio);
  newtio=oldtio; 
  newtio.c_cflag=0x18b2;
  newtio.c_lflag=0x0;
  newtio.c_iflag=0x1;
  newtio.c_oflag=0x0;
  newtio.c_ispeed=0xbffffd08;
  newtio.c_ospeed=0x40036e78;
  newtio.c_line=0x0;
  tcsetattr(s_port,TCSAFLUSH,&newtio);
  printf( "%s Set to 115,200 Baud 8n1\n",port_name,argc);
}
