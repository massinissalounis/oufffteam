public class serialPort extends java.lang.Object
{  
    // open serial port at specified baud with other appropriate parameters.
    // returns:
    // 0 on success
    // -1 on failure to open serial port
    // -2 on failure to read port state
    // -3 on failure to set port state
    // coms are: 1 = "COM1"; 2 = "COM2" et cetera    
    // baud rates are: 1 = 9600; 2=19200; 3=38400; 4=57600; 5=115200; 6=230400
    public synchronized native static int openSerial(int comNum, int baudSpec);
    public synchronized native static int closeSerial();
    // returns 0 on success or -1 on failure to send byte
    public synchronized native static int sendByte(int theByte);
    // initialTimeout is measured in milliseconds //
    // returns -6 on failure to set timeout, 0 on success
    public synchronized native static int setReadTimeout(int initialTimeout);
    // returns -1 in error or timeout, else returns int between 0 and 255
    public synchronized native static int readByte();
   
   static {
    System.loadLibrary("sserial");
   }
    
}
