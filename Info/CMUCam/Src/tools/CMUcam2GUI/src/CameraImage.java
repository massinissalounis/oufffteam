import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
import javax.imageio.*;
import javax.imageio.stream.*;
import javax.imageio.ImageWriteParam;

public class CameraImage extends JPanel implements Serializable {

	//JFrame picker_f;
	boolean pickerStat;
	public int mm;
	int mmx, mmy, mmoldx, mmoldy;
	char bmask[][];
	int lm, lmIndex, tc;
	int width, height;
	int pixels[];
	int backup[];
	int mx,
		my,
		xcoord,
		ycoord,
		zcoord,
		oldz,
		oldx,
		oldy,
		x2coord,
		y2coord,
		oldx2,
		oldy2,
		conf;
	MemoryImageSource source;
	BufferedImage image;
	//Image offScreenImage;
	//Graphics offScreenGC;
	//zoomBox azoomBox;
	JLabel red_l, green_l, blue_l;
	JPanel colorBox;
	int frames, fps;
	long startTime;
	int start;
	int flipx, flipy;
	long wdTimer;
	int scale;
	int rmin[], rmax[], gmin[], gmax[], bmin[], bmax[];
	static int objDirt[];
	int size_x, size_y;
	int objnum;
	int obj_x[], obj_y[];
	int target_x, target_y;
	double my_turn, my_drive;
	JFrame channel_f;
	int cur_chan;
	CameraImage(int x, int y) {
		objnum = 0;
		target_y = 0;
		target_x = 0;
		flipx = 0;
		flipy = 0;
		cur_chan = 4;
		rmin = new int[3];
		rmax = new int[3];
		gmin = new int[3];
		gmax = new int[3];
		bmin = new int[3];
		bmax = new int[3];
		obj_x = new int[3];
		obj_y = new int[3];
		objDirt = new int[3];
		bmask = new char[10][48];
		my_drive = 0;
		lmIndex = 0;
		mmoldx = 0;
		mmoldy = 0;
		mmx = 0;
		mmy = 0;
		mm = 1;
		lm = 0;
		scale = 0;
		start = 1;
		zcoord = 0;
		xcoord = 0;
		ycoord = 0;
		x2coord = 0;
		y2coord = 0;
		oldx = 0;
		oldy = 0;
		oldx2 = 0;
		oldy2 = 0;
		oldz = 0;
		conf = 0;
		tc = 0;
		pickerStat = false;
		//picker_f = new JFrame("Color Picker");
		JPanel picker_p = new JPanel();
		red_l = new JLabel("0");
		green_l = new JLabel("0");
		blue_l = new JLabel("0");
		//azoomBox = new zoomBox();
		colorBox = new JPanel();
		colorBox.setPreferredSize(new Dimension(32,32));
		//picker_f.setBackground(Color.lightGray);
	    GridLayout pickerLayout = new GridLayout(2, 4);
	    pickerLayout.setHgap(5);
		picker_p.setLayout(pickerLayout);
		
		picker_p.add(new JLabel());
		picker_p.add(new JLabel("Red"));
		picker_p.add(new JLabel("Green"));
		picker_p.add(new JLabel("Blue"));
		picker_p.add(new JLabel());
		picker_p.add(red_l);
		picker_p.add(green_l);
		picker_p.add(blue_l);
		JPanel pickerb_p = new JPanel();
		pickerb_p.setBorder(
			BorderFactory.createTitledBorder(
				BorderFactory.createEtchedBorder(),
				"Color Picker"));
		pickerb_p.add(colorBox);
		pickerb_p.add(picker_p);
		//pickerb_p.setBackground(Color.gray);
		MainWindow.status_t = new JTextField("starting up...");
		JPanel finalPicker = new JPanel();
		GridLayout agl = new GridLayout(2, 1);
		agl.setVgap(20);

		finalPicker.add(pickerb_p);

		MainWindow.JPanel1.add(finalPicker);

		pickerStat = true;
		setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
		enableEvents(
			AWTEvent.MOUSE_EVENT_MASK | AWTEvent.MOUSE_MOTION_EVENT_MASK);
		//col=0;
		//row=0;
		this.setBackground(Color.black);
		width = x;
		height = y;
		pixels = new int[width * height];
		backup = new int[width * height];
		//	source = new MemoryImageSource(width,height,pixels,0,width);
		//source.setAnimated(true);
		//image=createImage(source);
		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		image.setRGB(0, 0, width, height, pixels, 0, width);
		frames = 0;
		fps = 0;
		Date time = new Date();
		startTime = time.getTime();
		//myRaw = new rawWindow();
	}
	public void flip(int type) {
		int x, y;

		if (type == 0) {
			for (x = 0; x < width; x++)
				for (y = 0; y < height; y++) {
					backup[(y * width) + x] =
						pixels[(y * width) + (width - x - 1)];
				}
		} else {
			for (x = 0; x < width; x++)
				for (y = 0; y < height; y++) {
					backup[(y * width) + x] =
						pixels[((height - y - 1) * width) + x];
				}
		}

		for (x = 0; x < width * height; x++)
			pixels[x] = backup[x];
		image.setRGB(0, 0, width, height, pixels, 0, width);

		repaint();
	}

	public void setChannel(int chan) {
		int x;
		if (cur_chan == 4) {
			for (x = 0; x < width * height; x++)
				backup[x] = pixels[x];
		}

		int pix;
		int tmp;
		for (x = 0; x < width * height; x++) {
			cur_chan = chan;
			if (chan == 0) {
				tmp = backup[x] & 0xFF0000;
				pix = tmp | (tmp >> 8) | (tmp >> 16);
			} else if (chan == 1) {
				tmp = backup[x] & 0x00FF00;
				pix = tmp | (tmp << 8) | (tmp >> 8);
			} else if (chan == 2) {
				tmp = backup[x] & 0x0000FF;
				pix = tmp | (tmp << 8) | (tmp << 16);
			} else
				pix = backup[x];
			Color pixColor = new Color(pix);
			pixels[x] = pixColor.getRGB();
		}
		image.setRGB(0, 0, width, height, pixels, 0, width);

		repaint();
	}

	public void processEvent(AWTEvent e) {
		int r, g, b;
		mx = ((MouseEvent) e).getX();
		my = ((MouseEvent) e).getY();

		int tx, ty, pix, tmp;

		tx = mx - (getSize().width - width) / 2;
		ty = my - ((getSize().height - height) / 2) - 20;

		if (size_x == 160 && size_y == 288)
			ty -= 72; // Must be a type 4 mosaic
		if (size_x == 320 && size_y == 288)
			ty -= 72; // Must be a type 5 mosaic

		if (tx < 0 || ty < 0 || tx > width - 1 || ty > height - 1)
			pix = 0;
		else
			pix = pixels[ty * width + tx];
		Color pixColor = new Color(pix);
		colorBox.setBackground(pixColor);
		b = pix & 0xFF;
		blue_l.setText(String.valueOf(b));
		g = pix >> 8 & 0xFF;
		green_l.setText(String.valueOf(g));
		r = pix >> 16 & 0xFF;
		red_l.setText(String.valueOf(r));

		int button = ((MouseEvent) e).getButton();
		if (((MouseEvent) e).getClickCount() > 0 && button != 0) {

			if (my_drive != 0) {
			}
			if (button == 1) {

				objDirt[objnum] = 1;
				int tol = new Integer(MainWindow.tol_t.getText()).intValue();
				//int tol=25;
				rmin[objnum] = r - tol;
				if (rmin[objnum] < 0)
					rmin[objnum] = 0;
				rmax[objnum] = r + tol;
				if (rmax[objnum] > 255)
					rmax[objnum] = 255;
				gmin[objnum] = g - tol;
				if (gmin[objnum] < 0)
					gmin[objnum] = 0;
				gmax[objnum] = g + tol;
				if (gmax[objnum] > 255)
					gmax[objnum] = 255;
				bmin[objnum] = b - tol;
				if (bmin[objnum] < 0)
					bmin[objnum] = 0;
				bmax[objnum] = b + tol;
				if (bmax[objnum] > 255)
					bmax[objnum] = 255;
				MainWindow.rmin_t.setText(
					(new Integer(rmin[objnum])).toString());
				MainWindow.gmin_t.setText(
					(new Integer(gmin[objnum])).toString());
				MainWindow.bmin_t.setText(
					(new Integer(bmin[objnum])).toString());
				MainWindow.rmax_t.setText(
					(new Integer(rmax[objnum])).toString());
				MainWindow.gmax_t.setText(
					(new Integer(gmax[objnum])).toString());
				MainWindow.bmax_t.setText(
					(new Integer(bmax[objnum])).toString());
				int w_width = getSize().width;
				int w_height = getSize().height;

				int x_off = (w_width - width) / 2;
				int y_off = (w_height - height) / 2;

				obj_x[objnum] = mx - x_off;
				obj_y[objnum] = my - y_off;

			}
			if (objDirt[objnum] == 1) {
				int mmx = obj_x[objnum];
				if (my_drive == 0) {

				}

			}
			repaint();
		}
	}

	public void sendFrame(int chan) {
		int pix, x_off, y_off, x, y;
		int red, green, blue, data;
		int new_frame = 0, width_cnt;
		int x_max, y_max;

		//x_off=(width-size_x)/2;
		//y_off=(height-size_y)/2;
		for (x = 0; x < width * height; x++)
			pixels[x] = 0;
		x_off = 0;
		y_off = 0;
		x = 0;
		y = 0;
		width_cnt = 0;
		if (MainWindow.fs_c.getSelectedIndex() != 1) {
			MainWindow.mySerial.readACK(0);
			if (MainWindow.cameraVersion == 1)
				MainWindow.mySerial.write("df\r");
			else if (chan == 0)
				MainWindow.mySerial.write("sf\r");
			else {
				MainWindow.mySerial.write("sf " + (chan - 1) + "\r");
			}
		}
		MainWindow.status_t.setText("Frame Grab...");
		while (true) {
			//data=mainWindow.mySerial.sPort.readByte();
			data = MainWindow.mySerial.getByte();
			//	System.out.println( data );
			if (data == 0) {
				System.out.println("Data ==0");
				MainWindow.status_t.setText("Frame Grab Failed.");
				image.setRGB(0, 0, width, height, pixels, 0, width);

				repaint();
				return;
			}
			if (data == 1) {
				System.out.println("Got new Frame");
				new_frame = 1;
				if (MainWindow.cameraVersion == 2) {

					x_max = MainWindow.mySerial.getByte();
					y_max = MainWindow.mySerial.getByte();
					System.out.println(
						"X size: " + x_max + " Y size: " + y_max);
					MainWindow.frameProg.setMaximum(y_max - 1);
				} else {
					x_max = 80;
					y_max = 144;
					MainWindow.frameProg.setMaximum(80);
				}

				x = 0;
				y = 0;
				width_cnt = 0;
			} else if (data == 2) {

				if (MainWindow.cameraVersion == 2) {
					MainWindow.frameProg.setValue(y);
					System.out.println("Row " + y + " Width=" + width_cnt);
				} else {
					System.out.println("Rows: " + y + " Cols: " + x);
					MainWindow.frameProg.setValue(x / 2 + 1);
				}

				width_cnt = 0;
				if (MainWindow.cameraVersion == 1) {
					x += 2;
					y = 0;
				} else {
					x = 0;
					y++;
				}
				if (y > 288)
					y = 288;
				if (x > 352)
					x = 352;
			} else if (data == 3) {
				if (flipx == 1)
					flip(0);
				if (flipy == 1)
					flip(1);
				if (MainWindow.commandVal == 6)
					MainWindow.commandVal = 0;
				image.setRGB(0, 0, width, height, pixels, 0, width);
				repaint();
				MainWindow.status_t.setText("Frame Received");
				return;
			} else if (new_frame == 1) {
				width_cnt++;
				red = data;
				green = 0;
				blue = 0;
				if (chan == 0) {
					green = MainWindow.mySerial.getByte();
					blue = MainWindow.mySerial.getByte();
				} else {
					green = red;
					blue = red;
				}
				pix = 0;
				pix += blue;
				pix += green << 8;
				pix += red << 16;
				Color pixColor = new Color(pix);
				if (MainWindow.cameraVersion == 1) {
					pixels[((y + y_off) * width) + x + x_off] =
						pixColor.getRGB();
					pixels[((y + y_off) * width) + x + x_off + 1] =
						pixColor.getRGB();
					y++;
				} else {
					pixels[((y + y_off) * width) + x + x_off] =
						pixColor.getRGB();
					x++;
					pixels[((y + y_off) * width) + x + x_off] =
						pixColor.getRGB();
					x++;
				}
				if (y > 288)
					y = 288;
				if (x > 352)
					x = 352;
			}
		}
	}

	public boolean writeImage(String name) {
		boolean ret = false;
		ImageWriter w = null;
		BufferedImage blah = null;
		System.out.println("Trying to write...");

		try {

			Iterator writers = ImageIO.getImageWritersBySuffix("jpg");
			if (!(writers.hasNext())) {
				System.out.println("No readers for extension jpg");
				return false;
			}
			w = (ImageWriter) (writers.next());
			if (w == null) {
				System.out.println("No writers for extension jpg");
				return false;
			}

			File fo = new File(name);
			ImageOutputStream ios = ImageIO.createImageOutputStream(fo);
			w.setOutput(ios);
 
			ImageWriteParam iwparam = w.getDefaultWriteParam();
            		iwparam.setCompressionMode(ImageWriteParam.MODE_EXPLICIT) ;
            		iwparam.setCompressionQuality(1.0F);

			w.write(null, new IIOImage(image, null, null), iwparam);
			//w.write((BufferedImage) image,iwparam);
			System.out.println("File " + name + " written");
			ret = true;
			ios.close();
		} catch (Exception e) {
			System.out.println(e);
		}

		return true;
	}

	/*
	  This is where the bitmap and tracking boxes are drawn.
	  The actual background is add in update()
	*/
	public void paintComponent(Graphics g) {
		int x_off, y_off;
		int w_width, w_height;
		w_width = getSize().width;
		w_height = getSize().height;

		/*if (offScreenImage == null) {
			offScreenImage = createImage(getSize().width, getSize().height);
			offScreenGC = offScreenImage.getGraphics();
		}
		g.drawImage(offScreenImage, 0, 0, this);
		*/

		g.setColor(Color.black);
		g.fillRect(0, 0, w_width, w_height);
		x_off = (w_width - width) / 2;
		y_off = ((w_height - height) / 2) + 20;

		g.drawImage(image, x_off, y_off, this);

		for (int k = 0; k < 3; k++)
			if (objDirt[k] == 1) {
				if (k == 0)
					g.setColor(Color.cyan);
				else if (k == 1)
					g.setColor(Color.green);
				else if (k == 2)
					g.setColor(Color.magenta);
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width; x++) {
						int rr, gr, br, pix;
						pix = pixels[y * width + x];
						br = pix & 0xFF;
						gr = pix >> 8 & 0xFF;
						rr = pix >> 16 & 0xFF;

						if (rr < rmax[k]
							&& rr > rmin[k]
							&& gr < gmax[k]
							&& gr > gmin[k]
							&& br < bmax[k]
							&& br > bmin[k]) {

							g.fillRect(x + x_off, y + y_off, 1, 1);
						}

					}

			}
	}

}
