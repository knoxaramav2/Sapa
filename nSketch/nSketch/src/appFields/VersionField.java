package appFields;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;

/*
 * Extends text class
 * Validates field to conform to numeric 
 * version field:
 * integer.integer.integer
 * all positive
 */

public class VersionField extends TextField{
	
	@FXML private TextField text;

	public VersionField()
	{
		
	}
	
	@Override
	public void replaceText(int i, int j, String string)
	{
		if (string.matches("[0-9]")|| string.isEmpty())
			{
				super.replaceText(i, i, string);
			}
	}
	
	@Override
	public void replaceSelection(String string)
	{
		super.replaceSelection(string);
	}
	
}
