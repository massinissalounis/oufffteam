import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

public class ColorTrack extends JPanel /*implements Serializable*/ {
	int active, mx_g, my_g, x1_g, y1_g, x2_g, y2_g, pix_g, conf_g;
	MemoryImageSource source;
	Image image;
	int width;
	int height;
	int pixels[];

	ColorTrack() {
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

	public void stop() {
		active = 0;
	}

	public void trackColor() {
		int i;

		active = 1;

		if (MainWindow.mySerial.readTpacket() == 0) {
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
		pix_g = MainWindow.mySerial.pix;
		conf_g = MainWindow.mySerial.conf;
		//System.out.println( mx_g + " " + my_g + " " + x1_g +" "+ y1_g +" "+ x2_g +" "+ y2_g + " " + pix_g + " " + conf_g );
		repaint();
		/*Graphics g = getGraphics();
		paint(g);
		g.dispose();
		     }
		*/
		return;
	}

	public void paintComponent(Graphics g) {

		int w_width, w_height, i, ox, oy;
		int xSize, ySize;

		w_width = getSize().width;
		w_height = getSize().height;
		ox = (w_width - 320) / 2;
		oy = (w_height - 320) / 2;
		//g.setColor(Color.white);
		g.setColor(Color.darkGray);
		g.fillRect(0, 0, w_width + 1, w_height + 1);
		g.setColor(Color.green);
		g.drawRect(ox, oy, 320, 320);

		//for(int y=0; y<8; y++ ) g.drawRect(ox,oy+y*40,320,1);
		//for(int x=0; x<8; x++ ) g.drawRect(ox+x*40,oy,1,320);

		if (active == 1) {
			double xs, ys;
			if (MainWindow.hr_c.getSelectedIndex() == 0
				&& MainWindow.cameraType == 6) { // Low-Res
				xs = 3.63;
				ys = 2.22;
				//xSize=11;
				//ySize=141;
			} else { // Hi-Res
				xs = 1.82;
				ys = 1.27;
				/*if(mainWindow.cameraType==6)
				    {
					xSize=22;
					ySize=264;
				    }
				else
				    {
					xSize=20;
					ySize=237;
					}*/
			}
			if (MainWindow.cameraVersion == 1) {
				xs = 3.63;
				ys = 2.22;
			}
			if (mx_g == 0 && my_g == 0)
				return;
			x2_g++;
			y2_g++;
			g.setColor(Color.blue);
			g.fillRect(
				(int) (x1_g * xs + ox),
				(int) (y1_g * ys) + oy,
				(int) ((x2_g - x1_g) * xs),
				(int) ((y2_g - y1_g) * ys));
			g.setColor(Color.cyan);
			int vwX, vwY;
			vwX = (new Integer(MainWindow.x1.getText())).intValue();
			vwY = (new Integer(MainWindow.y1.getText())).intValue();
			vwX--;
			if (vwX < 0 || vwX > 255)
				vwX = 0;
			if (vwY < 0 || vwY > 255)
				vwY = 0;

			if (MainWindow.track_color_linemode == 1) {
				ySize = MainWindow.mySerial.lmHeight;
				xSize = MainWindow.mySerial.lmWidth;
				xSize = (xSize + 7) / 8;
				if (MainWindow.cameraVersion != 1) {
					for (int y = 0; y < ySize; y++)
						for (int x = 0; x < xSize; x++) {
							int isOn, t;
							for (t = 0; t < 8; t++) {
								if ((y * xSize) + x > 5999)
									return;
								isOn =
									MainWindow.mySerial.lineArray[(y * xSize)
										+ x] >> t;
								isOn = isOn & 1;
								if (isOn == 1) {
									g.setColor(Color.cyan);
									g.fillRect(
										ox
											+ (int) (((x * 8) + (8 - t) + vwX)
												* xs),
										oy + (int) ((y + vwY) * (ys)),
										(int) (xs + 1),
										(int) (ys + 1));
								}
								/*else
								  {
								  g.setColor(Color.black);
								  g.fillRect(ox+(int)(((x*8)+t)*xs),oy+(int)(y*ys),(int)xs,(int)ys);
								  }*/
							}

						}

				} else {
					// CMUcam1 linemode support
					ySize = ySize / 2;
					// half vertical resolution when in line mode
					for (int y = 0; y < ySize; y++)
						for (int x = 0; x < xSize; x++) {
							int isOn, t;
							for (t = 0; t < 8; t++) {
								if ((y * xSize) + x > 5999)
									return;
								isOn =
									MainWindow.mySerial.lineArray[(
										(ySize - y) * xSize)
										+ x] >> t;
								isOn = isOn & 1;
								if (isOn == 1) {
									g.setColor(Color.cyan);
									g.fillRect(
										ox
											+ (int) (((x * 8) + (8 - t) + vwX)
												* xs),
										oy + (int) ((y + vwY) * (4 * ys)),
										(int) (xs + 1),
										(int) (2 * ys + 1));
								}
								/*else
								  {
								  g.setColor(Color.black);
								  g.fillRect(ox+(int)(((x*8)+t)*xs),oy+(int)(y*ys),(int)xs,(int)ys);
								  }*/
							}

						}

				}
			}

			if (MainWindow.track_color_linemode == 2) {
				int lines;
				lines = MainWindow.mySerial.lmWidth;
				for (int line = 0; line < lines; line++) {
					int xLineMean, xLineMin, xLineMax, fCntLine, fConfLine;
					xLineMean = MainWindow.mySerial.lineArray[line * 5];
					xLineMin = MainWindow.mySerial.lineArray[line * 5 + 1];
					xLineMax = MainWindow.mySerial.lineArray[line * 5 + 2];
					fCntLine = MainWindow.mySerial.lineArray[line * 5 + 3];
					fConfLine = MainWindow.mySerial.lineArray[line * 5 + 4];
					if (xLineMean != 0) {
						g.setColor(Color.yellow);
						g.fillRect(
							ox + (int) (xs * xLineMin),
							oy + (int) (line * ys) + (int) (vwY * ys),
							(int) ((xLineMax - xLineMin) * xs + 1),
							(int) (ys + 1));
						g.setColor(Color.magenta);
						g.fillRect(
							ox + (int) (xs * xLineMean),
							oy + (int) (line * ys) + (int) (vwY * ys),
							(int) (xs + 1),
							(int) (ys + 1));
					}

				}
			}

			g.setColor(Color.red);
			g.fillRect((int) (mx_g * xs + ox), (int) (my_g * ys + oy), 4, 4);
		}

	}

}
