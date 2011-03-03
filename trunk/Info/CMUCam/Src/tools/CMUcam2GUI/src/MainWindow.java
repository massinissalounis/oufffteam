import java.awt.*;
import java.awt.event.*;
import java.io.File;

import javax.swing.*;
import javax.swing.event.*;

/*
  This object controls the way the GUI looks and handles the 
  menu events etc.  This is also where the serial config 
  can be found.
*/

public class MainWindow
	implements ActionListener, ItemListener, AdjustmentListener {
	static volatile int commandVal;
	JButton sendFrame_b;
	JButton saveFrame_b;
	Thread updateThread;
	static CameraImage cImage;
	volatile Motion myMotion;
	volatile ColorTrack myColor;
	volatile Histogram myHistogram;
	volatile Stats myStats;
	AboutWindow myAbout;
	int file_cnt, msg_cnt;
	JMenu images_m;
	JMenuBar menuBar;
	JFrame pref_f, scale_f;
	static JTextField thresh_t,
		nf_t,
		rmin_t,
		gmin_t,
		bmin_t,
		rmax_t,
		gmax_t,
		bmax_t;
	static JTextArea path_crl_t;
	static JTextField tol_t, time_t, size_t, port_t;
	JButton setParams_b;
	static JPanel cam_p, stats_p;
	static JPanel configb_p;
	static JPanel config_p;
	static JPanel settings_p;
	static JPanel servo_p;
	static JTextField xpos_t, ypos_t;
	static JTextField status_t;
	static JLabel servo0_l, servo1_l, servo2_l, servo3_l, servo4_l;
	static JScrollBar servo0_s, servo1_s, servo2_s, servo3_s, servo4_s;
	static JPanel JPanel1;
	static JComboBox whiteBalance;
	static JComboBox autoGain;
	static JComboBox fps;
	static JComboBox channel_c;
	static JComboBox hr_c;
	static JComboBox lm_c;
	static JComboBox as_c;
	static JComboBox color_c;
	static JComboBox bm_c;
	static JComboBox sf_chan_c;
	static JComboBox pd_c;
	static JComboBox ti_c;
	static JComboBox fs_c;
	static JComboBox hd_c;
	static JComboBox dc_c;
	static JLabel cFPS_l,mFPS_l,sFPS_l,hFPS_l;
	JButton clear_b;
	static CameraSerial mySerial;
	static int cameraType, cameraVersion;
	static int track_color_linemode, get_mean_linemode, frame_diff_linemode;
	static JTextField rmean_l, gmean_l, bmean_l;
	static JTextField x1, y1, x2, y2, dsx, dsy;
	static JTextField pan_range_far,
		pan_range_near,
		pan_step,
		tilt_range_far,
		tilt_range_near,
		tilt_step;
	volatile int res;
	JButton send_command_b;
	static JProgressBar frameProg;

	MainWindow() {
		res = 0;
		file_cnt = 0;
		msg_cnt = 0;
		track_color_linemode = 0;
		get_mean_linemode = 0;
		frame_diff_linemode = 0;
		CommWindow cWindow = new CommWindow(); // Serial Config Window
		while (cWindow.ready() == 0) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		JPanel1 = new JPanel();

		myAbout = new AboutWindow();
		JFrame main_f = new JFrame("CMUcam2 GUI");
		main_f.getContentPane().setLayout(new BorderLayout());
		main_f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		cam_p = new JPanel();
		config_p = new JPanel();

		tol_t = new JTextField("25", 5);
		JPanel select_p = new JPanel();
		select_p.add(new JLabel("Select Tolerance"));
		select_p.add(tol_t);
		clear_b = new JButton("clear");
		select_p.add(clear_b);
		clear_b.addActionListener(this);

		/**************************** Settings JPanel  **********************/
		JPanel settingspad_p = new JPanel();
		settings_p = new JPanel();
		GridLayout set_l = new GridLayout(13, 3);
		set_l.setVgap(10);
		set_l.setHgap(10);
		settings_p.setLayout(set_l);

		//settings_p.add(new JLabel(""));
		//settings_p.add(new JLabel(""));
		//settings_p.add(new JLabel(""));

		JLabel color_l = new JLabel("Color Space");
		color_c = new JComboBox();
		color_c.addItem("RGB");
		color_c.addItem("YCrCb");
		color_c.addItemListener(this);
		settings_p.add(color_l);
		settings_p.add(color_c);
		settings_p.add(new JLabel(""));
		//JButton setcs_b = new JButton( "Set Color" );
		//settings_p.add(setcs_b);
		//setcs_b.addActionListener(this);

		JLabel wb_l = new JLabel("White Balance");
		whiteBalance = new JComboBox();
		whiteBalance.addItem("Off");
		whiteBalance.addItem("On");
		whiteBalance.addItemListener(this);
		settings_p.add(wb_l);
		settings_p.add(whiteBalance);
		settings_p.add(new JLabel(""));
		//JButton setwb_b = new JButton( "Set WB" );
		//settings_p.add(setwb_b);
		//setwb_b.addActionListener(this);

		JLabel ag_l = new JLabel("Auto Gain");
		autoGain = new JComboBox();
		autoGain.addItem("On");
		autoGain.addItem("Off");
		autoGain.addItemListener(this);
		settings_p.add(ag_l);
		settings_p.add(autoGain);
		//JButton setag_b = new JButton( "Set Gain" );
		//settings_p.add(setag_b);
		//setag_b.addActionListener(this);
		settings_p.add(new JLabel(""));

		JLabel hr_l = new JLabel("Camera Resolution");
		hr_c = new JComboBox();
		hr_c.addItem("Low");
		hr_c.addItem("High");
		hr_c.addItemListener(this);
		settings_p.add(hr_l);
		settings_p.add(hr_c);
		settings_p.add(new JLabel(""));

		JLabel pd_l = new JLabel("Pixel Difference");
		pd_c = new JComboBox();
		pd_c.addItem("Off");
		pd_c.addItem("On");
		pd_c.addItemListener(this);
		settings_p.add(pd_l);
		settings_p.add(pd_c);
		settings_p.add(new JLabel(""));

		JLabel ti_l = new JLabel("Inverted Tracking");
		ti_c = new JComboBox();
		ti_c.addItem("Off");
		ti_c.addItem("On");
		ti_c.addItemListener(this);
		settings_p.add(ti_l);
		settings_p.add(ti_c);
		settings_p.add(new JLabel(""));

		JLabel fs_l = new JLabel("Frame Stream");
		fs_c = new JComboBox();
		fs_c.addItem("Off");
		fs_c.addItem("On");
		fs_c.addItemListener(this);
		settings_p.add(fs_l);
		settings_p.add(fs_c);
		settings_p.add(new JLabel(""));

		JLabel hd_l = new JLabel("HiRes Frame Diff");
		hd_c = new JComboBox();
		hd_c.addItem("Off");
		hd_c.addItem("On");
		hd_c.addItemListener(this);
		settings_p.add(hd_l);
		settings_p.add(hd_c);
		settings_p.add(new JLabel(""));

		JLabel dc_l = new JLabel("Diff Channel");
		dc_c = new JComboBox();
		dc_c.addItem("Red");
		dc_c.addItem("Green");
		dc_c.addItem("Blue");
		settings_p.add(dc_l);
		settings_p.add(dc_c);
		settings_p.add(new JLabel(""));
		dc_c.setSelectedIndex(1);
		dc_c.addItemListener(this);

		JLabel lm_l = new JLabel("Line Modes");
		lm_c = new JComboBox();
		lm_c.addItem("Off");
		lm_c.addItem("Track Color-Bitmap");
		lm_c.addItem("Track Color-Stats");
		lm_c.addItem("Get Mean data");
		lm_c.addItem("Get Mean data-stats");
		lm_c.addItem("Frame Diff-Bitmap");
		lm_c.addItem("Frame Diff-Deltas");
		lm_c.addItem("Frame Diff-Buffer");
		lm_c.addItemListener(this);
		settings_p.add(lm_l);
		settings_p.add(lm_c);
		//JButton setlm_b = new JButton( "Set LM" );
		//settings_p.add(setlm_b);
		//setlm_b.addActionListener(this);
		settings_p.add(new JLabel(""));

		JLabel bm_l = new JLabel("Buffer Mode");
		bm_c = new JComboBox();
		bm_c.addItem("Stream");
		bm_c.addItem("Single");
		bm_c.addItemListener(this);
		settings_p.add(bm_l);
		settings_p.add(bm_c);
		JButton setbm_b = new JButton("read frame");
		settings_p.add(setbm_b);
		setbm_b.addActionListener(this);

		JLabel nf_l = new JLabel("Noise Filter");
		nf_t = new JTextField("2", 5);
		settings_p.add(nf_l);
		settings_p.add(nf_t);
		JButton setnf_b = new JButton("Set NF");
		settings_p.add(setnf_b);
		setnf_b.addActionListener(this);

		JLabel rsa_l = new JLabel("Update All Parameters");
		settings_p.add(rsa_l);
		JButton rsa_b = new JButton( "Update ALL" );
		settings_p.add(rsa_b);
		rsa_b.addActionListener(this);
		settings_p.add(new JLabel(""));
		
		
		/*
		JButton regUpdate_b=new JButton("Set Reg");
		settings_p.add(regUpdate_b);
		regUpdate_b.addActionListener(this);
		*/

		//settings_p.add(servo_b);
		settingspad_p.setLayout(new BorderLayout());
		settingspad_p.add("Center", settings_p);
		JPanel vw_ds_p = new JPanel();
		vw_ds_p.setLayout(new BorderLayout());

		JPanel vw_p = new JPanel();
		vw_p.add(new JLabel("Virtual Window:"));
		x1 = new JTextField("100", 5);
		y1 = new JTextField("100", 5);
		x2 = new JTextField("100", 5);
		y2 = new JTextField("100", 5);
		vw_p.add(x1);
		vw_p.add(y1);
		vw_p.add(x2);
		vw_p.add(y2);
		JButton vw_b = new JButton("Set Window");
		vw_p.add(vw_b);
		vw_b.addActionListener(this);

		JPanel ds_p = new JPanel();
		ds_p.add(new JLabel("Down Sampling:"));
		ds_p.add(new JLabel("X Axis:"));
		dsx = new JTextField("1", 5);
		ds_p.add(dsx);
		ds_p.add(new JLabel("Y Axis:"));
		dsy = new JTextField("1", 5);
		ds_p.add(dsy);
		JButton ds_b = new JButton("Down Sample");
		ds_p.add(ds_b);
		ds_b.addActionListener(this);
		vw_ds_p.add("North", ds_p);
		vw_ds_p.add("South", vw_p);
		//vw_ds_p.add("East", rsa_b);
		settingspad_p.add("South", vw_ds_p);
		
		/****************************   Servo JPanel    **********************/
		JPanel servopad_p = new JPanel();
		servo_p = new JPanel();
		GridLayout set2_l = new GridLayout(12, 3);
		set2_l.setVgap(10);
		set2_l.setHgap(10);
		servo_p.setLayout(set2_l);

		JLabel as_l = new JLabel("Auto Servo");
		as_c = new JComboBox();
		as_c.addItem("Off");
		as_c.addItem("On");
		as_c.addItemListener(this);
		servo_p.add(as_l);
		servo_p.add(as_c);
		//JButton setres_b = new JButton( "Set Res" );
		//settings_p.add(setres_b);
		//setres_b.addActionListener(this);
		servo_p.add(new JLabel(""));

		JLabel servo0 = new JLabel("Servo 0:");
		servo0_s = new JScrollBar(JScrollBar.HORIZONTAL, 127, 1, 0, 255);
		JLabel servo1 = new JLabel("Servo 1:");
		servo1_s = new JScrollBar(JScrollBar.HORIZONTAL, 127, 1, 0, 255);
		JLabel servo2 = new JLabel("Servo 2:");
		servo2_s = new JScrollBar(JScrollBar.HORIZONTAL, 127, 1, 0, 255);
		JLabel servo3 = new JLabel("Servo 3:");
		servo3_s = new JScrollBar(JScrollBar.HORIZONTAL, 127, 1, 0, 255);
		JLabel servo4 = new JLabel("Servo 4:");
		servo4_s = new JScrollBar(JScrollBar.HORIZONTAL, 127, 1, 0, 255);

		servo0_l = new JLabel("127");
		servo1_l = new JLabel("127");
		servo2_l = new JLabel("127");
		servo3_l = new JLabel("127");
		servo4_l = new JLabel("127");

		//    JButton servo_b = new JButton("Set Servos");
		servo_p.add(servo0);
		servo_p.add(servo0_s);
		servo_p.add(servo0_l);
		servo_p.add(servo1);
		servo_p.add(servo1_s);
		servo_p.add(servo1_l);
		servo_p.add(servo2);
		servo_p.add(servo2_s);
		servo_p.add(servo2_l);
		servo_p.add(servo3);
		servo_p.add(servo3_s);
		servo_p.add(servo3_l);
		servo_p.add(servo4);
		servo_p.add(servo4_s);
		servo_p.add(servo4_l);

		servo0_s.addAdjustmentListener(this);
		servo1_s.addAdjustmentListener(this);
		servo2_s.addAdjustmentListener(this);
		servo3_s.addAdjustmentListener(this);
		servo4_s.addAdjustmentListener(this);

		pan_range_far = new JTextField("16", 5);
		pan_range_near = new JTextField("8", 5);
		pan_step = new JTextField("5", 5);
		tilt_range_far = new JTextField("30", 5);
		tilt_range_near = new JTextField("15", 5);
		tilt_step = new JTextField("5", 5);
		servo_p.add(new JLabel("pan range far:"));
		servo_p.add(pan_range_far);
		servo_p.add(new JLabel(""));
		servo_p.add(new JLabel("pan range near:"));
		servo_p.add(pan_range_near);
		servo_p.add(new JLabel(""));
		servo_p.add(new JLabel("pan step:"));
		servo_p.add(pan_step);
		servo_p.add(new JLabel(""));
		servo_p.add(new JLabel("tilt range far:"));
		servo_p.add(tilt_range_far);
		servo_p.add(new JLabel(""));
		servo_p.add(new JLabel("tilt range near:"));
		servo_p.add(tilt_range_near);
		servo_p.add(new JLabel(""));
		servo_p.add(new JLabel("tilt step:"));
		servo_p.add(tilt_step);
		JButton update_servo_b = new JButton("Config Servos");
		servo_p.add(update_servo_b);
		update_servo_b.addActionListener(this);

		/****************************   Stats JPanel    **********************/
		myStats = new Stats();
		JPanel statistics_p = new JPanel();
		statistics_p.setLayout(new BorderLayout());
		JPanel stats_p = new JPanel();
		stats_p.add(new JLabel("FPS"));
						sFPS_l=new JLabel("0");
						stats_p.add(sFPS_l);
						stats_p.add(new JLabel("      "));
		JLabel rgb_l = new JLabel("RGB:");
		stats_p.add(rgb_l);
		rmean_l = new JTextField("0", 5);
		stats_p.add(rmean_l);
		gmean_l = new JTextField("0", 5);
		stats_p.add(gmean_l);
		bmean_l = new JTextField("0", 5);
		stats_p.add(bmean_l);

		JButton stats_b = new JButton("Get Mean");
		stats_p.add(stats_b);
		stats_b.addActionListener(this);
		
		statistics_p.add("Center", myStats);
		statistics_p.add("South", stats_p);
		/**************************** Histogram JPanel  **********************/
		myHistogram = new Histogram();
		JPanel histogram_p = new JPanel();
		histogram_p.setLayout(new BorderLayout());
		JPanel hist_p = new JPanel();

		hist_p.add(new JLabel("FPS"));
		hFPS_l=new JLabel("0");
		hist_p.add(hFPS_l);
		hist_p.add(new JLabel("      "));
								
		channel_c = new JComboBox();
		channel_c.addItem("Red (Cr)");
		channel_c.addItem("Green (Y)");
		channel_c.addItem("Blue (Cb)");
		channel_c.addItemListener(this);
		hist_p.add(channel_c);

		JButton hist_b = new JButton("Get Histogram");
		hist_p.add(hist_b);
		hist_b.addActionListener(this);
		
		histogram_p.add("Center", myHistogram);
		histogram_p.add("South", hist_p);

		/****************************  Color Tracking JPanel  ***************/
		myColor = new ColorTrack();
		JPanel color_p = new JPanel();
		JPanel col_p = new JPanel();
		color_p.setLayout(new BorderLayout());
		
		rmin_t = new JTextField("0", 5);
		gmin_t = new JTextField("0", 5);
		bmin_t = new JTextField("0", 5);
		rmax_t = new JTextField("0", 5);
		gmax_t = new JTextField("0", 5);
		bmax_t = new JTextField("0", 5);

		col_p.add(new JLabel("min:"));
		col_p.add(rmin_t);
		col_p.add(gmin_t);
		col_p.add(bmin_t);

		col_p.add(new JLabel("max:"));
		col_p.add(rmax_t);
		col_p.add(gmax_t);
		col_p.add(bmax_t);

		JPanel colb_p = new JPanel();
		colb_p.setLayout(new BorderLayout());
		JPanel tc_p = new JPanel();
		tc_p.add(new JLabel("FPS:"));
						cFPS_l=new JLabel("0");
						tc_p.add(cFPS_l);
				tc_p.add(new JLabel("     "));
		JButton color_b = new JButton("Track Color");
		tc_p.add(color_b);
		color_b.addActionListener(this);

		JButton tw_b = new JButton("Track Window");
		tc_p.add(tw_b);
		tw_b.addActionListener(this);
		
		colb_p.add("Center", col_p);
		colb_p.add("South", tc_p);
		color_p.add("Center", myColor);
		color_p.add("South", colb_p);

		/****************************  Motion Tracking JPanel  ***************/
		myMotion = new Motion();
		JPanel motion_p = new JPanel();
		JPanel mot_p = new JPanel();
		mot_p.add(new JLabel("FPS"));
				mFPS_l=new JLabel("0");
				mot_p.add(mFPS_l);
		mot_p.add(new JLabel("     "));
		motion_p.setLayout(new BorderLayout());
		thresh_t = new JTextField("15", 5);
		mot_p.add(new JLabel("Threshold:"));
		mot_p.add(thresh_t);

		JButton loadframe_b = new JButton("Load Frame");
		mot_p.add(loadframe_b);
		loadframe_b.addActionListener(this);

		JButton motion_b = new JButton("Frame Diff");
		mot_p.add(motion_b);
		motion_b.addActionListener(this);
		
		motion_p.add("Center", myMotion);
		motion_p.add("South", mot_p);

		/******************************* Main Image JPanel  *****************/

		cImage = new CameraImage(352, 288);
		JPanel ctmp_p = new JPanel();
		JPanel dtmp_p = new JPanel();
		sendFrame_b = new JButton("Grab Frame");
		saveFrame_b = new JButton("Save Frame");

		frameProg = new JProgressBar(0, 144);
		frameProg.setValue(0);
		frameProg.setStringPainted(true);
		frameProg.setOrientation(JProgressBar.HORIZONTAL);
		frameProg.setStringPainted(false);
		sf_chan_c = new JComboBox();
		sf_chan_c.addItem("All");
		sf_chan_c.addItem("red");
		sf_chan_c.addItem("green");
		sf_chan_c.addItem("blue");

		sendFrame_b.addActionListener(this);
		saveFrame_b.addActionListener(this);
		ctmp_p.add(sf_chan_c);
		ctmp_p.add(sendFrame_b);
		ctmp_p.add(saveFrame_b);

		// Make menus and such
		JTabbedPane tabPane1 = new JTabbedPane();

		//JPanel motion_p = new JPanel();

		menuBar = new JMenuBar();
		JMenu file_m = new JMenu("File");
		file_m.add(makeMenuItem("About"));
		file_m.add(makeMenuItem("Quit"));
		images_m = new JMenu("Image", true);
		images_m.add(makeMenuItem("Flip Vertical"));
		images_m.add(makeMenuItem("Flip Horizontal"));
		images_m.add(makeMenuItem("Red Channel"));
		images_m.add(makeMenuItem("Green Channel"));
		images_m.add(makeMenuItem("Blue Channel"));
		images_m.add(makeMenuItem("All Channels"));
		JPanel main_p = new JPanel();
		menuBar.add(file_m);
		menuBar.add(images_m);
		main_f.setJMenuBar(menuBar);

		// main_f.add("Center",cImage);
		main_p.setLayout(new BorderLayout());
		main_p.add("Center", cImage);

		JPanel argh = new JPanel();
		GridLayout kl = new GridLayout(2, 1);

		argh.setLayout(kl);
		argh.add(select_p);
		argh.add(ctmp_p);

		dtmp_p.setLayout(new BorderLayout());
		dtmp_p.add(argh, "Center");
		dtmp_p.add(frameProg, "South");
		JPanel1.add(dtmp_p);

		main_p.add("South", JPanel1);

		tabPane1.addTab("Camera View", main_p);
		tabPane1.addTab("Config", settingspad_p);
		tabPane1.addTab("Color", color_p);
		tabPane1.addTab("Motion", motion_p);
		tabPane1.addTab("Histogram", histogram_p);
		tabPane1.addTab("Stats", statistics_p);
		tabPane1.addTab("Servo", servo_p);
		tabPane1.setSelectedIndex(0);

		tabPane1.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				stopCameraStuff();
			}
		});

		JPanel topPain_p = new JPanel();
		topPain_p.add(new JLabel("Console:"));
		status_t = new JTextField(25);
		topPain_p.add(status_t);
		JButton stop_b = new JButton("STOP");
		topPain_p.add(stop_b);
		stop_b.addActionListener(this);
		JButton reset_b = new JButton("RESET");
		topPain_p.add(reset_b);
		reset_b.addActionListener(this);

		JButton clr_command_b = new JButton("Clear");
		topPain_p.add(clr_command_b);
		clr_command_b.addActionListener(this);

		JButton send_command_b = new JButton("Send");
		topPain_p.add(send_command_b);
		send_command_b.addActionListener(this);

		main_f.getContentPane().add(topPain_p, "North");
		main_f.getContentPane().add(tabPane1, "Center");

		//main_f.setSize(500, 620);
		main_f.pack();
		main_f.setVisible(true);
		/* updateThread=new Thread(new Runnable() { 
		   public void run() {pollCrl();}
		   });
		   updateThread.start();
		*/
		mySerial = new CameraSerial(cWindow.getPort());

		if (cameraType == 6) {
			x1.setText("1");
			y1.setText("1");
			x2.setText("87");
			y2.setText("142");
		} else {
			x1.setText("1");
			y1.setText("1");
			x2.setText("159");
			y2.setText("238");

		}
		commandVal = 0;
		while (true) {
			if (commandVal == 1)
				myMotion.trackMotion(hd_c.getSelectedIndex());
			else if (commandVal == 2)
				myHistogram.getHistogram();
			else if (commandVal == 3)
				myColor.trackColor();
			else if (commandVal == 4)
				myStats.getMean();
			else if (commandVal == 5 || commandVal == 6)
				cImage.sendFrame(sf_chan_c.getSelectedIndex());
			else if (commandVal == -1) {
				stopCameraStuff();
			} else {
				try {
					Thread.sleep(100);
				} catch (Exception e) {
				}
			}
		}

	}

	/*private void pollCrl()
	  {
	  FileInputStream fi;
	  int tempVal=-1,cnt;
	  
	  while(true)
	  {
	  int new_file=1;
	  String fname = new String( "img_log/image" + file_cnt + ".ppm");
	  try{
	  fi = new FileInputStream(fname);
	  fi.close();
	  }catch(Exception e) {new_file=0;}
	
	  if(new_file==1)
	  {
	  images_m.add(makeMenuItem(fname));
	  tempVal=cImage.loadImage(fname);
	  file_cnt++;
	  }
	
	  try{  
	  Thread.sleep(1);
	  } catch(InterruptedException e) {}
	
	  }
	
	  }*/

	/*
	  This is where the menus do clean up and set the commandVal value.
	*/
	public void actionPerformed(ActionEvent e) {
		String command = e.getActionCommand();

		if (commandVal != 0) {
			commandVal = -1;
			while (commandVal == -1)
				try {
					Thread.sleep(100);
				} catch (InterruptedException d) {
				}
		} else if (command.equals("Flip Horizontal")) {
			cImage.flip(0);
			if (cImage.flipx == 0)
				cImage.flipx = 1;
			else
				cImage.flipx = 0;
		} else if (command.equals("Flip Vertical")) {
			cImage.flip(1);
			if (cImage.flipy == 0)
				cImage.flipy = 1;
			else
				cImage.flipy = 0;
		} 
		else if (command.equals("Red Channel"))
			cImage.setChannel(0);
		else if (command.equals("Green Channel"))
			cImage.setChannel(1);
		else if (command.equals("Blue Channel"))
			cImage.setChannel(2);
		else if (command.equals("All Channels"))
			cImage.setChannel(4);
		else if (command.equals("Quit"))
			System.exit(0);
		else if (command.equals("About")) {
			myAbout.about_f.pack();
			myAbout.about_d.setVisible(true);
		} else if (command.equals("STOP")) {
			status_t.setText("Stopping...");
			commandVal = -1;
		} else if (command.equals("Send")) {
			mySerial.write(status_t.getText() + "\r");
			status_t.setText("Command Sent");
		} else if (command.equals("Config Servos")) {
			status_t.setText("Servo Configure Called");

			mySerial.write(
				"sp "
					+ pan_range_far.getText()
					+ " "
					+ pan_range_near.getText()
					+ " "
					+ pan_step.getText()
					+ " "
					+ tilt_range_far.getText()
					+ " "
					+ tilt_range_near.getText()
					+ " "
					+ tilt_step.getText());

			if (mySerial.readACK(1) == 1)
				status_t.setText("Servos Set.");
			else
				status_t.setText("Servo Config Failed.");
		} else if (command.equals("Clear")) {
			status_t.setText("");
		} else if (command.equals("RESET")) {
			commandVal = 0;
			as_c.setSelectedIndex(0);
			hr_c.setSelectedIndex(0);
			lm_c.setSelectedIndex(0);
			whiteBalance.setSelectedIndex(0);
			autoGain.setSelectedIndex(0);
			color_c.setSelectedIndex(0);
			bm_c.setSelectedIndex(0);
			hd_c.setSelectedIndex(0);
			ti_c.setSelectedIndex(0);
			pd_c.setSelectedIndex(0);
			dc_c.setSelectedIndex(1);
			mySerial.readACK(0);
			setWindowParams();
			mySerial.write("rs\r");
			mySerial.readACK(0);
			status_t.setText("Camera Reset...");
		} else if (command.equals("Grab Frame")) {
			if (fs_c.getSelectedIndex() == 1) {
				int chan = sf_chan_c.getSelectedIndex();
				if (chan == 0)
					mySerial.write("sf\r");
				else {
					mySerial.write("sf " + (chan - 1) + "\r");
				}

				commandVal = 5;
			} else
				commandVal = 6;

		} else if (command.equals("Save Frame")) {
			/*
			JFileChooser chooser=new JFileChooser();
			chooser.setSelectedFile(new File("default.jpg"));
			int returnval=chooser.showSaveDialog(save);
			if (returnval==JFileChooser.APPROVE_OPTION) {
			cImage.writeImage( chooser.getSelectedFile().getName());
			//trainCanvas.save(chooser.getSelectedFile().getName());
			}*/
			JFileChooser save_d = new JFileChooser();
			int result =
				save_d.showSaveDialog(
					new JFrame("Type the name of the File to save"));
			File saveFile = save_d.getSelectedFile();
			if (result == JFileChooser.APPROVE_OPTION) {
				cImage.writeImage(saveFile + ".jpg");
			}
		} else if (command.equals("clear")) {

			cImage.objnum = 0;
			cImage.my_drive = 0;
			cImage.target_x = 0;
			cImage.target_y = 0;
			CameraImage.objDirt[0] = 0;
			CameraImage.objDirt[1] = 0;
			CameraImage.objDirt[2] = 0;
			cImage.repaint();

		} else if (command.equals("Get Mean")) {
			status_t.setText("Get Mean");
			if (mySerial.readACK(0) == 0) {
				status_t.setText("Get Mean Failed");
				return;
			}

			mySerial.write("gm\r");
			MainWindow.status_t.setText("Get Mean ");

			commandVal = 4;
		} else if (command.equals("read frame")) {
			mySerial.write("rf");
			if (mySerial.readACK(0) == 0) {
				MainWindow.status_t.setText("Read Frame Failed");
				return;
			}
			MainWindow.status_t.setText("New Frame Loaded...");
		} else if (command.equals("Load Frame")) {
			if (mySerial.readACK(0) == 0) {
				status_t.setText("Load Frame Failed");
				return;
			}
			mySerial.write("lf");
			if (frame_diff_linemode == 3) {
				mySerial.write("\r");
				myMotion.trackMotion(hd_c.getSelectedIndex());
			} else if (mySerial.readACK(1) == 0) {
				MainWindow.status_t.setText("Load Frame Failed");
				return;
			}
			MainWindow.status_t.setText("Frame Loaded...");
		} else if (command.equals("Set Window")) {

			status_t.setText("Set Virtual Window Called");

			mySerial.write(
				"vw "
					+ x1.getText()
					+ " "
					+ y1.getText()
					+ " "
					+ x2.getText()
					+ " "
					+ y2.getText());

			if (mySerial.readACK(1) == 1)
				status_t.setText("Virtual Window Set.");
			else
				status_t.setText("Virtual Window Failed.");

		} else if (command.equals("Down Sample")) {

			status_t.setText("Down Sampling Called");

			mySerial.write("ds " + dsx.getText() + " " + dsy.getText());

			if (mySerial.readACK(1) == 1)
				status_t.setText("Down Sampling Set.");
			else
				status_t.setText("Down Sampling Failed.");

		} else if (command.equals("Track Color")) {

			status_t.setText("Track Color Called");
			if (mySerial.readACK(0) == 0) {
				status_t.setText("Tracking Failed");
				return;
			}
			mySerial.write(
				"tc "
					+ rmin_t.getText()
					+ " "
					+ rmax_t.getText()
					+ " "
					+ gmin_t.getText()
					+ " "
					+ gmax_t.getText()
					+ " "
					+ bmin_t.getText()
					+ " "
					+ bmax_t.getText()
					+ "\r");
			MainWindow.status_t.setText("Tracking Color ");

			commandVal = 3;
		} else if (command.equals("Track Window")) {

			status_t.setText("Track Window Called");

			if (mySerial.readACK(0) == 0) {
				status_t.setText("Tracking Failed");
				return;
			}

			mySerial.write("tw\r");

			setWindowParams();
			MainWindow.status_t.setText("Tracking Window ");
			commandVal = 3;
		} else if(command.equals("Update ALL"))
		{
			UpdateAllCommands();
		} else if (command.equals("Set NF")) {
			status_t.setText("Setting Noise Filter");
			mySerial.write("nf " + nf_t.getText());
			if (mySerial.readACK(1) == 1)
				status_t.setText("Noise Filter Set.");
			else
				status_t.setText("Noise Filter Failed.");
		} else if (command.equals("Frame Diff")) {

			status_t.setText("Frame Diff Called");
			if (mySerial.readACK(0) == 0) {
				status_t.setText("Tracking Failed");
				return;
			}
			mySerial.write("fd " + thresh_t.getText() + "\r");
			MainWindow.status_t.setText("Motion Track " + thresh_t.getText());

			commandVal = 1;
		} else if (command.equals("Get Histogram")) {

			status_t.setText("Get Histogram");
			if (mySerial.readACK(0) == 0) {
				status_t.setText("Histogram Failed");
				return;
			}

			mySerial.write("gh " + channel_c.getSelectedIndex() + "\r");
			MainWindow.status_t.setText(
				"Get Histogram " + channel_c.getSelectedIndex());

			commandVal = 2;
		}
		/* else
		{
		     int t=cImage.loadImage(command);
		}
		*/
	}

	public void adjustmentValueChanged(AdjustmentEvent e) {
		if (commandVal != 0) {
			commandVal = -1;
			while (commandVal == -1)
				try {
					Thread.sleep(100);
				} catch (InterruptedException d) {
				}
		}
		status_t.setText("Setting Servos");
		mySerial.write("sv 0 " + servo0_s.getValue() + "\r");
		mySerial.write("sv 1 " + servo1_s.getValue() + "\r");
		mySerial.write("sv 2 " + servo2_s.getValue() + "\r");
		mySerial.write("sv 3 " + servo3_s.getValue() + "\r");
		mySerial.write("sv 4 " + servo4_s.getValue() + "\r");
		servo0_l.setText((new Integer(servo0_s.getValue())).toString());
		servo1_l.setText((new Integer(servo1_s.getValue())).toString());
		servo2_l.setText((new Integer(servo2_s.getValue())).toString());
		servo3_l.setText((new Integer(servo3_s.getValue())).toString());
		servo4_l.setText((new Integer(servo4_s.getValue())).toString());
		status_t.setText("Servos Set");
	}

	private void setWindowParams() {
		if (res == 0) {
			if (cameraType == 6) {
				x1.setText("1");
				y1.setText("1");
				x2.setText("87");
				y2.setText("142");
			} else {
				x1.setText("1");
				y1.setText("1");
				x2.setText("159");
				y2.setText("238");

			}
		} else {
			x2.setText("174");
			y2.setText("254");
		}

	}
	/*
	  This is for check box menus
	*/
	public void itemStateChanged(ItemEvent e) {
		ItemSelectable command = e.getItemSelectable();

		if (commandVal != 0) {
			commandVal = -1;
			while (commandVal == -1)
				try {
					Thread.sleep(100);
				} catch (InterruptedException d) {
				}
		}
		if (command == autoGain ) {
			int ag;
			status_t.setText("Setting Auto Gain");
			if (autoGain.getSelectedIndex() == 0)
				ag = 33;
			else
				ag = 32;
			mySerial.write("cr 19 " + ag);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Registers Set.");
			else
				status_t.setText("Registers Failed.");
		} else if (command == whiteBalance || command == color_c) {
			int wb;
			if (color_c.getSelectedIndex() == 0) {
				if (whiteBalance.getSelectedIndex() == 0)
					wb = 40;
				else
					wb = 44;
			} else {
				if (whiteBalance.getSelectedIndex() == 0)
					wb = 32;
				else
					wb = 36;
			}
			status_t.setText("Setting Color and WB");
			mySerial.write("cr 18 " + wb);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Registers Set.");
			else
				status_t.setText("Registers Failed.");
		} else if (command == hr_c) {

			if (hr_c.getSelectedIndex() == 0) {
				res = 0;
				status_t.setText("Setting Res Low");

			} else {
				if (cameraType == 7) {
					status_t.setText("Option not available");
					return;
				}
				res = 1;
				status_t.setText("Setting Res High");

			}
			mySerial.write("hr " + res);
			if (mySerial.readACK(1) == 1) {
				status_t.setText("Registers Set.");
				setWindowParams();
			} else
				status_t.setText("Registers Failed.");
		} else if (command == as_c) {
			int as;
			if (as_c.getSelectedIndex() == 0)
				as = 0;
			else
				as = 1;
			mySerial.write("sm " + as);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Auto Servo Mode set.");
			else
				status_t.setText("Auto Servo Mode failed.");
		} else if (command == pd_c) {
			int pd;
			if (pd_c.getSelectedIndex() == 0)
				pd = 0;
			else
				pd = 1;
			mySerial.write("pd " + pd);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Pixel Differencing set.");
			else
				status_t.setText("Pixel Differencing failed.");
		} else if (command == ti_c) {
			int ti;
			if (ti_c.getSelectedIndex() == 0)
				ti = 0;
			else
				ti = 1;
			mySerial.write("ti " + ti);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Inverted Tracking set.");
			else
				status_t.setText("Inverted Tracking failed.");
		} else if (command == fs_c) {
			int fs;
			if (fs_c.getSelectedIndex() == 0)
				fs = 0;
			else
				fs = 1;
			mySerial.write("fs " + fs);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Frame Stream set.");
			else
				status_t.setText("Frame Stream failed.");
		} else if (command == hd_c) {
			int hd;
			if (hd_c.getSelectedIndex() == 0)
				hd = 0;
			else
				hd = 1;
			mySerial.write("hd " + hd);
			if (mySerial.readACK(1) == 1)
				status_t.setText("HiRes Diff Mode set.");
			else
				status_t.setText("HiRes Diff Mode failed.");
		} else if (command == dc_c) {
			int dc;
			mySerial.write("dc " + dc_c.getSelectedIndex());
			if (mySerial.readACK(1) == 1)
				status_t.setText("Diff Channel Set");
			else
				status_t.setText("Diff Channel Failed");
		} else if (command == bm_c) {
			int bm;
			if (bm_c.getSelectedIndex() == 0) {
				bm = 0;
				status_t.setText("Setting buffer mode auto stream");
			} else {
				bm = 1;
				status_t.setText("Setting buffer mode manual reload");
			}
			mySerial.write("bm " + bm);
			if (mySerial.readACK(1) == 1)
				status_t.setText("Buffer Mode Set.");
			else
				status_t.setText("Buffer Mode Failed.");

		} else if (command == lm_c) {
			int lm;

			track_color_linemode = 0;
			get_mean_linemode = 0;
			frame_diff_linemode = 0;

			switch (lm_c.getSelectedIndex()) {
				case 0 :
					lm = 0;
					status_t.setText("All line modes off");
					mySerial.write("lm 0 0");
					mySerial.readACK(1);
					mySerial.write("lm 1 0");
					mySerial.readACK(1);
					mySerial.write("lm 2 0");
					break;
				case 1 :
					status_t.setText("Line Mode Track Color Bitmap on");
					mySerial.write("lm 0 1");
					track_color_linemode = 1;
					break;
				case 2 :
					status_t.setText("Line Mode Track Color Stats on");
					mySerial.write("lm 0 2");
					track_color_linemode = 2;
					break;
				case 3 :
					status_t.setText("Line Mode Get Mean on");
					mySerial.write("lm 1 1");
					get_mean_linemode = 1;
					break;
				case 4 :
					status_t.setText("Line Mode Get Mean Stats on");
					mySerial.write("lm 1 2");
					get_mean_linemode = 2;
					break;
				case 5 :
					status_t.setText("Line Mode Frame Diff Bitmap on");
					mySerial.write("lm 2 1");
					frame_diff_linemode = 1;
					break;
				case 6 :
					status_t.setText("Line Mode Frame Diff Deltas on");
					mySerial.write("lm 2 2");
					frame_diff_linemode = 2;
					break;
				case 7 :
					status_t.setText("Line Mode Frame Diff Buffer on");
					mySerial.write("lm 2 3");
					frame_diff_linemode = 3;
					break;

				default :

					}

			if (mySerial.readACK(1) == 1)
				status_t.setText("Registers Set.");
			else
				status_t.setText("Registers Failed.");
		}

		String item = e.getItem().toString();
		int action = e.getStateChange();
		if (item.equals("Color Picker")) {
			// if(action==2)cImage.picker_f.hide();
			//else cImage.picker_f.show();    
		}

		if (item.equals("Color Track")) {
			//if(action==2)cImage.hideTrack();
			//else cImage.showTrack();    
		}

	}

	private JMenuItem makeMenuItem(String name) {
		JMenuItem m = new JMenuItem(name);
		m.addActionListener(this);
		return m;

	}

	private void stopCameraStuff() {
		myMotion.stop();
		myHistogram.stop();
		myColor.stop();
		myStats.stop();
		commandVal = 0;
		mySerial.write("\r");
		//if(mySerial.readACK(0)==0)mySerial.readACK(0);
		// Maintain state after track window
		status_t.setText("Camera Ready...");
	}


	private void UpdateAllCommands() {
			// This updates the Line Mode Window
			mySerial.write("lm 0 0");
			mySerial.readACK(1);
			mySerial.write("lm 1 0");
			mySerial.readACK(1);
			mySerial.write("lm 2 0");
			switch (lm_c.getSelectedIndex()) {
				case 1 : mySerial.write("lm 0 1"); track_color_linemode = 1; break;
				case 2 : mySerial.write("lm 0 2"); track_color_linemode = 2; break;
				case 3 : mySerial.write("lm 1 1"); get_mean_linemode = 1; break;
				case 4 : mySerial.write("lm 1 2"); get_mean_linemode = 2; break;
				case 5 : mySerial.write("lm 2 1"); frame_diff_linemode = 1; break;
				case 6 : mySerial.write("lm 2 2"); frame_diff_linemode = 2; break; 
				case 7 : mySerial.write("lm 2 3"); frame_diff_linemode = 3; break;

				default :
					}

			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
		
			int ag;
			if (autoGain.getSelectedIndex() == 0)
				ag = 33;
			else
				ag = 32;
			mySerial.write("cr 19 " + ag);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }

			int wb;
			if (color_c.getSelectedIndex() == 0) {
				if (whiteBalance.getSelectedIndex() == 0)
					wb = 40;
				else
					wb = 44;
			} else {
				if (whiteBalance.getSelectedIndex() == 0)
					wb = 32;
				else
					wb = 36;
			}
			mySerial.write("cr 18 " + wb);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }


			if (hr_c.getSelectedIndex() == 0) {
				res = 0;
				status_t.setText("Setting Res Low");

			} else {
				if (cameraType == 7) {
					status_t.setText("Option not available");
					return;
				}
				res = 1;
				status_t.setText("Setting Res High");

			}
			mySerial.write("hr " + res);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			
			int as;
			if (as_c.getSelectedIndex() == 0)
				as = 0;
			else
				as = 1;
			mySerial.write("sm " + as);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			

			int pd;
			if (pd_c.getSelectedIndex() == 0)
				pd = 0;
			else
				pd = 1;
			mySerial.write("pd " + pd);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			int ti;
			if (ti_c.getSelectedIndex() == 0)
				ti = 0;
			else
				ti = 1;
			mySerial.write("ti " + ti);
			
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			int fs;
			if (fs_c.getSelectedIndex() == 0)
				fs = 0;
			else
				fs = 1;
			mySerial.write("fs " + fs);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			

			int hd;
			if (hd_c.getSelectedIndex() == 0)
				hd = 0;
			else
				hd = 1;
			mySerial.write("hd " + hd);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			

			int dc;
			mySerial.write("dc " + dc_c.getSelectedIndex());
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			
			int bm;
			if (bm_c.getSelectedIndex() == 0) {
				bm = 0;
				status_t.setText("Setting buffer mode auto stream");
			} else {
				bm = 1;
				status_t.setText("Setting buffer mode manual reload");
			}
			mySerial.write("bm " + bm);
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }

			mySerial.write("nf " + nf_t.getText());
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			mySerial.write("ds " + dsx.getText() + " " + dsy.getText());
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			mySerial.write(
				"vw "
					+ x1.getText()
					+ " "
					+ y1.getText()
					+ " "
					+ x2.getText()
					+ " "
					+ y2.getText());
			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }
			mySerial.write(
				"sp "
					+ pan_range_far.getText()
					+ " "
					+ pan_range_near.getText()
					+ " "
					+ pan_step.getText()
					+ " "
					+ tilt_range_far.getText()
					+ " "
					+ tilt_range_near.getText()
					+ " "
					+ tilt_step.getText());

			if (mySerial.readACK(1) != 1)
				{ status_t.setText("Registers Failed."); return; }


		status_t.setText("Config Settings Sent");
	}

	private JCheckBoxMenuItem makeCheckMenuItem(String name, int val) {
		JCheckBoxMenuItem m = new JCheckBoxMenuItem(name);
		if (val == 1)
			m.setState(true);
		else
			m.setState(false);
		m.addItemListener(this);
		return m;

	}
}
