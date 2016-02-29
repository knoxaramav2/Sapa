package system;

import javafx.scene.control.Label;

/*
 * This class adds standard output utility
 */

public class SysIO {

	static public void print(String msg, Label li)
	{
		System.out.println(msg);
		li.setText(msg);
	}
	
}
