import java.awt.*;
import java.awt.image.*;

import javax.swing.*;

public class Motion extends JPanel /*implements Serializable*/ {
	int active, mx_g, my_g, x1_g, y1_g, x2_g, y2_g, pix_g, conf_g;
	MemoryImageSource source;
	Image image;
	int width;
	int height;
	int hires;
	int pixels[];
	Motion() {
		active = 0;
		setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
		//enableEvents(AWTEvent.MOUSE_EVENT_MASK |
		//	     AWTEvent.MOUSE_MOTION_EVENT_MASK);
		width = getSize().width;
		height = getSize().height;
		pixels = new int[width * height];
		source = new MemoryImageSource(width, height, pixels, 0, width);
		source.setAnimated(true);
		image = createImage(source);

	}

	/* public void processEvent(AWTEvent e)
	{
	
	repaint();
	
	int button=((MouseEvent)e).getButton();
	if( e.getID()==MouseEvent.MOUSE_PRESSED && button==1)
	    {
	
	    }
	 
	    } */

	public void trackMotion(int res) {
		int i;

		active = 1;
		hires = res;
		if (MainWindow.mySerial.readTpacket() == 0) {
			if (MainWindow.mySerial.lineArray[1] != 0) {
				mx_g = 0;
				my_g = 0;
				x1_g = 0;
				y1_g = 0;
				x2_g = 0;
				y2_g = 0;
				hires = 0;
				active = 1;
				repaint();
				return;
			}
			System.out.println("Aborting Track...");
			MainWindow.commandVal = -1;
			active = 0;
			repaint();
			return;
		}
		mx_g = MainWindow.mySerial.mx;
		my_g = MainWindow.mySerial.my;
		x1_g = MainWindow.mySerial.x1;
		y1_g = MainWindow.mySerial.y1;
		x2_g = MainWindow.mySerial.x2;
		y2_g = MainWindow.mySerial.y2;

		mx_g--;
		my_g--;
		x1_g--;
		y1_g--;
		x2_g--;
		y2_g--;
		//System.out.println( mx_g + " " + my_g + " " + x1_g +" "+ y1_g +" "+ x2_g +" "+ y2_g );
		repaint();

		return;
	}

	public void stop() {
		active = 0;
	}

	public void paintComponent(Graphics g) {

		int w_width, w_height, i, ox, oy;

		w_width = getSize().width;
		w_height = getSize().height;
		ox = (w_width - 320) / 2;
		oy = (w_height - 320) / 2;
		//g.setColor(Color.white);
		g.setColor(Color.darkGray);
		g.fillRect(0, 0, w_width, w_height);
		g.setColor(Color.green);
		g.drawRect(ox, oy, 320, 320);

		if (hires == 1) {
			for (int y = 0; y < 16; y++)
				g.drawRect(ox, oy + y * 20, 320, 1);
			for (int x = 0; x < 16; x++)
				g.drawRect(ox + x * 20, oy, 1, 320);
		} else {
			for (int y = 0; y < 8; y++)
				g.drawRect(ox, oy + y * 40, 320, 1);
			for (int x = 0; x < 8; x++)
				g.drawRect(ox + x * 40, oy, 1, 320);
		}

		if (active == 1) {

			if (mx_g != -1 && my_g != -1) {

				x2_g++;
				y2_g++;
				g.setColor(Color.blue);
				if (hires == 1)
					g.fillRect(
						x1_g * 20 + ox,
						y1_g * 20 + oy,
						(x2_g - x1_g) * 20,
						(y2_g - y1_g) * 20);
				else
					g.fillRect(
						x1_g * 40 + ox,
						y1_g * 40 + oy,
						(x2_g - x1_g) * 40,
						(y2_g - y1_g) * 40);
				g.setColor(Color.green);
				if (hires == 1)
					g.fillRect(mx_g * 20 + ox, my_g * 20 + oy, 20, 20);
				else
					g.fillRect(mx_g * 40 + ox, my_g * 40 + oy, 40, 40);
			}
			if (MainWindow.frame_diff_linemode == 1) {
				// Draw linemode data
				int index = 0;
				int max;
				max = 8;
				if (hires == 1)
					max = 16;
				for (int y = 0; y < max; y++) {
					for (int x = 0; x < 8; x++) {
						int isOn;
						isOn = MainWindow.mySerial.lineArray[index] << x;
						isOn = isOn & 0x80;
						if (isOn == 0x80) {
							g.setColor(Color.red);
							if (hires == 1)
								g.fillRect(
									ox + x * 20 + 1,
									oy + y * 20 + 1,
									18,
									18);
							else
								g.fillRect(
									ox + x * 40 + 1,
									oy + y * 40 + 1,
									38,
									38);
						}
					}
					index++;
					if (hires == 1) {
						for (int x = 0; x < 8; x++) {
							int isOn;
							isOn = MainWindow.mySerial.lineArray[index] << x;
							isOn = isOn & 0x80;
							if (isOn == 0x80) {
								g.setColor(Color.red);
								g.fillRect(
									ox + (x + 8) * 20 + 1,
									oy + y * 20 + 1,
									18,
									18);
							}
						}
						index++;
					}
				}
			}

			if (MainWindow.frame_diff_linemode == 2
				|| MainWindow.frame_diff_linemode == 3) {
				int index = 0;
				int max = 8;
				if (hires == 1)
					max = 16;
				for (int y = 0; y < max; y++) {
					for (int x = 0; x < max; x++) {
						int pix, val;
						pix = 0;
						val = MainWindow.mySerial.lineArray[index];
						pix = val;
						pix = pix << 8;
						pix += val;
						pix = pix << 8;
						pix += val;
						Color pixColor = new Color(pix);
						g.setColor(pixColor);
						if (hires == 1)
							g.fillRect(
								ox + x * 20 + 1,
								oy + y * 20 + 1,
								18,
								18);
						else
							g.fillRect(
								ox + x * 40 + 1,
								oy + y * 40 + 1,
								38,
								38);
						index++;
					}
				}

			}
		}

	}

}
