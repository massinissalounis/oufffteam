/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * This file is part of CMUcamGUI, a java program that helps     *
 * interface with the CMUcam Vision Board.                       *
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
import java.io.*;
import java.util.*;

/*
This file was a first attempt at making a cross platform
program.  This may seem strange, but this program switches
serial functions based on the OS.  Eventually I might get
around to using the java serial calls, but for now this
seems to work.
*/

public class SerialComm
{
    FileOutputStream sPortOut;
    FileInputStream sPortIn;
    int os;
    SerialComm(String commPort)
    {
	String tempOs = new String( System.getProperty("os.name"));
	if(tempOs.startsWith("Windows")) os=0;
	   else
	   os=1;
	if(os==0)
	    {//Windows
		System.out.println( "Windows Detected" );
		 int error;
        	error = serialPort.openSerial(new Integer(commPort).intValue(), 5);
        
        	if (error != 0) {
            	System.err.println("Error " + error + " during openSerial()");
		System.exit(0);
        	}
		serialPort.setReadTimeout(50); //Illah - make this much smaller?
        
        	System.out.println("serial port successfully opened!");     

	    }
	else
	    { // Unix Serial Init
		System.out.println( "Unix Based System Detected" );
		try{
		    sPortIn = new FileInputStream( commPort );
		    sPortOut = new FileOutputStream( commPort );
		}
		catch(Exception e){ System.out.println(e);}
	    }
    }
    /*
      Reads in an ascii number and returns an int.
      This function blocks.
      It returns -1 on failure
    */
    public int readNum()
    {
	char one,two,three,four;
	one=readByte();
	if(one==0) return -1;
	two=readByte();
	if(two==0) return -1;
	if( two==' '|| two=='\r' )
	    return((int)(one-'0'));
	three=readByte();
	if(three==0) return -1;
	if( three==' ' || three=='\r' )
	    return((int)(one-'0')*10+(two-'0'));
	four=readByte();
	if(four==0) return -1;
	return((int)(one-'0')*100+(two-'0')*10+(three-'0'));
     
    }

    public char readByte()
    {
	 Date time = new Date();
	 long wdTimer=time.getTime();
	if(os==0)
	    {//Windows
		int val=-1;
		while(val==-1)
			{
			val = serialPort.readByte();
			Date time2 = new Date();
			    if(time2.getTime()-wdTimer>1000) 
				{
				    System.out.println("Waiting for Serial data..."); 
				    return 0; 
				}

			}
		return((char)val);
	    }
	else
	    { // Unix Serial Init
		try{
		    while(sPortIn.available()==0 )
			{ 
			    Date time2 = new Date();
			    if(time2.getTime()-wdTimer>100) 
				{
				    System.out.println("Waiting for Serial data..."); 
				    return 0; 
				}
			}
		    return((char)sPortIn.read());
		} catch(Exception e){System.out.println(e); }
	    }
	return 0;
    }
    
    public char readNonBlock()
    {
	if(os==0)
	    {//Windows
		int val;
		val = serialPort.readByte();
		if(val==-1) val=0;
		return((char)val);
	    }
	else
	    { // Unix Serial Init
		try{
		    if(sPortIn.available()==0 ) { 
			return 0; 
		    }
		    return((char)sPortIn.read());
		} catch(Exception e){System.out.println(e); }
	    }
	return 0;
    }

       
    public void writeStr(String in)
    {	
	if(os==0)
	    {//Windows
        	int i;
        	byte[] bytes = in.getBytes();        
        	for (i = 0; i < bytes.length; i++) {
		    int error = serialPort.sendByte(bytes[i]);
		    if (error != 0) {
                	System.out.println( "Serial Send error" );
			break;
		    }
		}        
				
	    }
	else
	    { // Unix Serial Init
		try{
		    sPortOut.write(in.getBytes());
		} catch(Exception e){System.out.println(e); }	
	    }
    }
}
