import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

public class Histogram extends JPanel /*implements Serializable*/ {
	int active, mx_g, my_g, x1_g, y1_g, x2_g, y2_g, pix_g, conf_g;
	MemoryImageSource source;
	Image image;
	int width;
	int height;
	int pixels[];
	Histogram() {
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

	public void getHistogram() {
		int i;
		active = 1;

		if (MainWindow.mySerial.readHpacket() == 0) {
			System.out.println("Aborting H packet read...");
			MainWindow.commandVal = -1;
			active = 0;
			repaint();
			return;
		}
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

		// Motion Middle Mass
		if (active == 1) {
			if (MainWindow.channel_c.getSelectedIndex() == 0)
				g.setColor(Color.red);
			else if (MainWindow.channel_c.getSelectedIndex() == 1)
				g.setColor(Color.green);
			else
				g.setColor(Color.blue);

			for (int x = 0; x < 28; x++) {
				int pt;
				pt = MainWindow.mySerial.histogram[x];
				if (pt > 160)
					pt = 160;
				g.fillRect(
					x * 10 + ox + 15,
					oy + 2 * (160 - pt),
					10,
					320 - (2 * (160 - pt)));

			}

		}

	}

}
