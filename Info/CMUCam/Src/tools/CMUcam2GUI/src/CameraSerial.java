import java.util.*;

/**************************************
  This class is a set of higher level
  serial functions that use the commands
  in serialComm.java
***************************************/

public class CameraSerial
{
   
    /***********************************************************************/
    /*                          T PACKET GLOBALS                           */
    /*                                                                     */
    /*            These get set when readTpacket() gets called             */
    /*                                                                     */
    /***********************************************************************/
    public int mx,my,x1,x2,y1,y2,pix,conf,fps,cnt;
    
    /***********************************************************************/
    /*                          S PACKET GLOBALS                           */
    /*                                                                     */
    /*            These get set when readSpacket() gets called             */
    /*                                                                     */
    /***********************************************************************/
    public int rmean,gmean,bmean,rdev,gdev,bdev;

    /***********************************************************************/
    /*                          H PACKET GLOBALS                           */
    /*                                                                     */
    /*            This array gets set when readHpacket() gets called       */
    /*                                                                     */
    /***********************************************************************/
    public int[] histogram;

    /***********************************************************************/
    /*                          Line Mode GLOBALS                          */
    /*                                                                     */
    /*            This array gets set when line mode is on,                */
    /*            lmWidth and lmHeight are calculated based on the frame   */
    /*            to tell you the width and height of the binary image     */
    /***********************************************************************/
    public int[] lineArray;
    public int lnCount;
    public int lmWidth,lmHeight;
   
    /**********************  Other random Globals   ************************/
    long startTime;
    int block;
    static SerialComm sPort;

    CameraSerial(String port)
    {
	int data,i;
	block=0;
	mx=5;
	my=3;
	histogram=new int[29];
	lineArray = new int[6000];
	// Start up the serial connection and see if the CMUcam is available
	Date time=new Date();
	startTime=time.getTime();
	fps=0;
	sPort=new SerialComm(port);
	MainWindow.status_t.setText("Looking for Camera...");
	sPort.writeStr("\r");
	try{ Thread.sleep(100); } catch(Exception e){}
	data=1;
	while(data!=0)
	    data=sPort.readByte();
	for(i=0; i<3; i++ )
	    {
		sPort.writeStr("rs\r");
		data=sPort.readByte();
		while(data!='m')
		    data=sPort.readByte();
		data=sPort.readByte();
		if(data==' ') 
		    {
			MainWindow.cameraVersion=1;
			MainWindow.cameraType=6;
			break;
		    }
		else
		    if(data=='2')  
			{
			    MainWindow.cameraVersion=2;
			    break;
			}
		    else MainWindow.cameraVersion=-1;
	    }

	data=0;
	if(MainWindow.cameraVersion==2) 
	    {
		while(data!='c')	
		    data=sPort.readByte();
		data=sPort.readByte();
		if(data=='6')
		    MainWindow.cameraType=6;
		else if(data=='7')
		    MainWindow.cameraType=7;
		else
		    MainWindow.cameraType=-1;
		
		if(MainWindow.cameraVersion==-1)
		    {
			MainWindow.status_t.setText("Unknown Camera Version.");
			return;
		    }
		if(MainWindow.cameraType==-1)
		    {
			MainWindow.status_t.setText("Unknown CMOS sensor Type.");
			return;
		    }
	    }
	for(i=0; i<3; i++ )
	    {
		if(readACK(1)==1)
		    {
			MainWindow.status_t.setText("CMUcam Version " + MainWindow.cameraVersion + " type " + MainWindow.cameraType + " ready.");
			break;
		    }
		else
		    {
		    MainWindow.status_t.setText("Camera not found.");

		    }
	    }

	
    }

    public char getByte()
    {
	char temp;
	temp=sPort.readByte();
	return temp;
    }
    
    public void write(String in)
    {
	sPort.writeStr(in);
    }

    //  When check=0 it keeps trying to get an ACK
    //  When check=1 it gives up right away
    public int readACK(int check)
    {
	int state, data,flag;
	int okay=1;
	while(block==1);
	block=1;
	state=0;
	sPort.writeStr("\r");
	data=sPort.readByte();
	while(true)
	    {
		flag=0;
		if(state==4 && data==':' ) {block=0;  return okay; }
		if(state==3 && data=='\r' ) { state=4; flag=1;}
		if(state==2 && data=='K' ) { state=3; flag=1;}
		if(state==1 && data=='C' ) { state=2; flag=1;}
		if(data=='A') { state=1; flag=1; }
		data=sPort.readByte();
		if(data==0) 
		    {
			while(data==0)
			    {
				if(check==1) okay=0;
				//error mode... Just try and reset again...
				try{  
				    Thread.sleep(100);
				} catch(InterruptedException e) {}
				sPort.writeStr("\r");
				try{  
				    Thread.sleep(100);
				} catch(InterruptedException e) {}
				for(int q=0; q<1000; q++ ) 
				    {
					data=sPort.readByte();
					if(data!=0) break;
				    }
				/*if(data==0)
				  {
				  // I give up...
				  System.out.println( "ACK failed" ); 
				  return 0; 
				  }*/
			    }
		    }
		if(flag==0)state=0;
	    }
     
	
    }


    public int readSpacket()
    {
	int data;
	data=0;

	while(data!='S')
	    {
		data=sPort.readByte();
		if(data==0xFE) 
		    {
			data=sPort.readByte();
			lnCount=0;
			while(true)
			    {
			
				lineArray[lnCount]=data;
				lnCount++;
				data=sPort.readByte();
				if(data==0xFD) 
				    {
					System.out.print( "Line Count: " + lnCount + " " );
					break;
				    }
			    }
			data=sPort.readByte();
			if(data==0) { MainWindow.status_t.setText("S packet failed"); return 0; }
		    }
		if(data==0) { MainWindow.status_t.setText("S packet failed"); return 0; }
	    }
	data=sPort.readByte(); if(data==0) return 0; // space
	rmean=sPort.readNum(); if(rmean==-1) return 0;
	gmean=sPort.readNum(); if(gmean==-1) return 0;
	bmean=sPort.readNum(); if(bmean==-1) return 0;
	rdev=sPort.readNum();  if(rdev==-1) return 0;
	gdev=sPort.readNum();  if(gdev==-1) return 0;
	bdev=sPort.readNum();  if(bdev==-1) return 0;
	updateFPS();
	MainWindow.sFPS_l.setText((new Integer(fps)).toString());
	System.out.print( "FPS: " + fps + " S: " + rmean + " " + gmean + " "
			  + bmean + " " + rdev + " " + gdev + " " + bdev + "\n");
	return 1;
	    }

    public int readHpacket()
    {
	int data,i;
	if(MainWindow.cameraVersion==1)
	    {
		MainWindow.status_t.setText("Not Supported on CMUcam 1");
		return 0;
	    }
	data=0;
	while(data!='H')
	    {
		data=sPort.readByte();
		if(data==0)
		    {
			MainWindow.status_t.setText("H packet failed");
			return 0;
		    }
	    }
	data=sPort.readByte();  // space
	for(i=0; i<28; i++ )
	    histogram[i]=sPort.readNum();
	
	updateFPS();
	MainWindow.hFPS_l.setText((new Integer(fps)).toString());
	System.out.print( "FPS: " + fps + " H: " );
	for(i=0; i<28; i++ )
	    System.out.print( histogram[i] + " " );
	System.out.println("");

	return 1;

    }
    public int readTpacket()
    {
	int data;
	int lmstate,calc_width;
	char start_char;
	calc_width=0;
	data=0;
	lnCount=0;
	start_char='T';
	if(MainWindow.cameraVersion==1) start_char='M';
	while(data!=start_char)
	    {
		data=sPort.readByte();
		int line_mode_type=0;
		if(data==0xAA || data==0xFC || data==0xFE) 
		    {
			int r=0;
			line_mode_type=data;
			if(MainWindow.cameraVersion!=1)
			    {
				lmWidth=sPort.readByte();
				if(MainWindow.track_color_linemode!=2) lmHeight=sPort.readByte();
				//if((lmWidth%8)!=0)r=1;
				//lmWidth=lmWidth/8+r;
				// You are in line mode
				//lmstate=0;
			    }
			else
			    {
				lmWidth=10;
				lmHeight=72;

			    }
			data=sPort.readByte();
			//lmWidth=0;
			while(true)
			    {
				lineArray[lnCount]=data;
				lnCount++;
				if(lnCount>5999)lnCount=5999;
				data=sPort.readByte();
				if(data==0xAA && line_mode_type==0xAA) break;
				if(data==0xFD && line_mode_type==0xFC) break; 
				if(data==0xFD && line_mode_type==0xFE) break; 
				    
			    }
			data=sPort.readByte();
			if(lmWidth==0)lmWidth=1;
			//lmHeight=lnCount/lmWidth;
			System.out.print( "Line mode: " + lmWidth + "," + lmHeight + " " );
			//data=sPort.readByte();
			       
		    }
		if(data==0)
		    {
			MainWindow.status_t.setText("Track packet failed");
			return 0;
		    }
	    }
	data=sPort.readByte();  if(data==0) return 0; // space
	mx=sPort.readNum();     if(mx==-1) return 0;
	my=sPort.readNum();     if(my==-1) return 0;
	x1=sPort.readNum();     if(x1==-1) return 0;
	y1=sPort.readNum();	if(y1==-1) return 0;
	x2=sPort.readNum();     if(x2==-1) return 0;
	y2=sPort.readNum();     if(y2==-1) return 0;
	pix=sPort.readNum();    if(pix==-1) return 0;
	conf=sPort.readNum();	if(conf==-1) return 0;
	updateFPS();
	MainWindow.cFPS_l.setText((new Integer(fps)).toString());
	MainWindow.mFPS_l.setText((new Integer(fps)).toString());
	System.out.println( "FPS: " + fps + " T: " + mx + " " + my + " " + x1 +" "+ y1 +" "+ x2 +" "+ y2 + " " + pix + " " + conf );
	return 1;

    }

    private void updateFPS()
    {
	cnt++;	
	Date time=new Date();
	if((time.getTime()-startTime)>1000 )
	    {
		fps=cnt;
		startTime=time.getTime();
		cnt=0;
	    }

    }
}
