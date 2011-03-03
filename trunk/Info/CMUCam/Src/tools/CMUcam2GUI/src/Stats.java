import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

public class Stats extends JPanel {
	int active, rmean, gmean, bmean, rdev, gdev, bdev;
	MemoryImageSource source;
	Image image;
	
	int width;
	int height;
	int pixels[];
	int tmp_lines;
	Stats() {
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

	public void getMean() {
		int i;
		active = 1;

		if (MainWindow.mySerial.readSpacket() == 0) {
			System.out.println("Aborting S packet read...");
			MainWindow.commandVal = -1;
			active = 0;
			repaint();
			return;
		}

		MainWindow.rmean_l.setText(
			new Integer(MainWindow.mySerial.rmean).toString());
		MainWindow.gmean_l.setText(
			new Integer(MainWindow.mySerial.gmean).toString());
		MainWindow.bmean_l.setText(
			new Integer(MainWindow.mySerial.bmean).toString());

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
		ox = (w_width - 20) / 2;
		oy = (w_height - 320) / 2;
		//g.setColor(Color.white);
		g.setColor(Color.darkGray);
		g.fillRect(0, 0, w_width, w_height);
		g.setColor(Color.green);
		g.drawRect(ox, oy, 20, 321);
		g.drawRect(ox - 60, oy, 20, 321);
		g.drawRect(ox + 60, oy, 20, 321);

		// Get Mean
		if (active == 1) {
			int lines;
			double yScale;
			lines = MainWindow.mySerial.lineArray[0];
			if (MainWindow.get_mean_linemode == 0)
				lines = 1;
			yScale = 320.0 / lines;
			for (int y = 0; y < lines; y++) {
				int pt, c, lo, hi, r, gn, b;
				hi = 0;
				lo = 0;
				if (MainWindow.get_mean_linemode != 2) {
					r = MainWindow.mySerial.rmean - MainWindow.mySerial.rdev;
					if (r < 0)
						r = 0;
					if (r > 255)
						r = 255;
					gn = MainWindow.mySerial.gmean - MainWindow.mySerial.gdev;
					if (gn < 0)
						gn = 0;
					if (gn > 255)
						gn = 255;
					b = MainWindow.mySerial.bmean - MainWindow.mySerial.bdev;
					if (b < 0)
						b = 0;
					if (b > 255)
						b = 255;
					lo = b + (gn << 8) + (r << 16);
					r = MainWindow.mySerial.rmean + MainWindow.mySerial.rdev;
					if (r < 0)
						r = 0;
					if (r > 255)
						r = 255;
					gn = MainWindow.mySerial.gmean + MainWindow.mySerial.gdev;
					if (gn < 0)
						gn = 0;
					if (gn > 255)
						b = 255;
					b = MainWindow.mySerial.bmean + MainWindow.mySerial.bdev;
					if (b < 0)
						b = 0;
					if (b > 255)
						b = 255;
					hi = b + (gn << 8) + (r << 16);
				}
				c = 0;
				if (MainWindow.get_mean_linemode == 0) {
					yScale--;
					c =
						MainWindow.mySerial.bmean
							+ (MainWindow.mySerial.gmean << 8)
							+ (MainWindow.mySerial.rmean << 16);

				} else if (MainWindow.get_mean_linemode == 1)
					c =
						MainWindow.mySerial.lineArray[y * 3
							+ 3]
							+ (MainWindow.mySerial.lineArray[y * 3 + 2] << 8)
							+ (MainWindow.mySerial.lineArray[y * 3 + 1] << 16);
				else if (MainWindow.get_mean_linemode == 2) {
					int r_tmp, g_tmp, b_tmp;
					c =
						MainWindow.mySerial.lineArray[y * 6
							+ 3]
							+ (MainWindow.mySerial.lineArray[y * 6 + 2] << 8)
							+ (MainWindow.mySerial.lineArray[y * 6 + 1] << 16);
					r_tmp = MainWindow.mySerial.lineArray[y * 6 + 4];
					g_tmp = MainWindow.mySerial.lineArray[y * 6 + 5];
					b_tmp = MainWindow.mySerial.lineArray[y * 6 + 6];

					r = MainWindow.mySerial.lineArray[y * 6 + 1] - r_tmp;
					if (r < 16)
						r = 16;
					gn = MainWindow.mySerial.lineArray[y * 6 + 2] - g_tmp;
					if (gn < 16)
						gn = 16;
					b = MainWindow.mySerial.lineArray[y * 6 + 3] - b_tmp;
					if (b < 16)
						b = 16;
					lo = b + (gn << 8) + (r << 16);

					r = MainWindow.mySerial.lineArray[y * 6 + 1] + r_tmp;
					if (r > 255)
						r = 255;
					gn = MainWindow.mySerial.lineArray[y * 6 + 2] + g_tmp;
					if (gn > 255)
						gn = 255;
					b = MainWindow.mySerial.lineArray[y * 6 + 3] + b_tmp;
					if (b > 255)
						b = 255;
					hi = b + (gn << 8) + (r << 16);
				}

				Color pixColor = new Color(c);
				g.setColor(pixColor);
				g.fillRect(
					ox + 1,
					(int) (oy + 1 + (yScale * y)),
					19,
					(int) yScale + 1);

				Color lopixColor = new Color(lo);
				g.setColor(lopixColor);
				g.fillRect(
					ox + 1 - 60,
					(int) (oy + 1 + (yScale * y)),
					19,
					(int) yScale + 1);
				//g.fillRect(ox+1-60,oy+1,19,320);
				Color hipixColor = new Color(hi);
				g.setColor(hipixColor);
				g.fillRect(
					ox + 1 + 60,
					(int) (oy + 1 + (yScale * y)),
					19,
					(int) yScale + 1);
				//g.fillRect(ox+1+60,oy+1,19,320);
			}

		}

	}

}
