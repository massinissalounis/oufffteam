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
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class CommWindow extends JPanel {
	private JTextField comm_t;
	private JFrame comm_d;
	int done;

	CommWindow() {
		done = 0;
		String tempOs = new String(System.getProperty("os.name"));
		if (tempOs.startsWith("Windows"))
			comm_t = new JTextField("1", 5);
		else
			comm_t = new JTextField("/dev/ttyS0", 5);

		JButton comm_b = new JButton("OK");
		comm_b.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				done = 1;
			}
		});

		comm_d = new JFrame("Serial Port Select");
		comm_d.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		comm_d.getContentPane().add(new JLabel("Select serial port "));
		comm_d.getContentPane().setLayout(new FlowLayout());
		comm_d.getContentPane().add(comm_t);
		comm_d.getContentPane().add(comm_b);
		comm_d.setBounds(50,50,200,100);
	//	comm_d.pack();
		comm_d.show();
	}

	public String getPort() {
		return comm_t.getText();
	}
	public int ready() {
		if (done == 0)
			return 0;
		comm_d.setVisible(false);
		return 1;
	}

}
