import java.awt.event.*;
import javax.swing.*;

public class AboutWindow {
	JFrame about_f;
	JPanel about_p;
	JDialog about_d;

	AboutWindow() {
		about_f = new JFrame();
		about_p = new JPanel();

		JTextArea about_t =
			new JTextArea("This is the CMUcam2 GUI v1.0.5\n\nThis program was designed to help you test features of the CMUcam2.\nIt is also compatible with the CMUcam1, but not highly supported.\n\nWritten by Anthony Rowe, Fall 2003\n\nSpecial Thanks to Adam Goode for fixing things up.");

		JButton about_b = new JButton("Ok");
		about_b.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				about_d.setVisible(false);
			}
		});
		about_d = new JDialog(about_f, "About CMUcamGUI");
		about_p.add("Center", about_t);
		about_p.add("South", about_b);
		about_d.getContentPane().add(about_p);
		//about_d.getContentPane().setBounds(50, 50, 510, 230);
		about_d.pack();
		about_d.hide();

	}

}
