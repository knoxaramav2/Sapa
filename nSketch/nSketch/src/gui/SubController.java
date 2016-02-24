package gui;

import appFields.VersionField;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import system.Settings;

public class SubController {
	
	//User mutable data
	Settings settings = null;
	
	@FXML private TextField prjSetName;
	@FXML private VersionField prjVers;
	@FXML private Button prjSetCancel;
	@FXML private Button prjSetConfirm;
	
	public SubController(Settings st)
	{
		System.out.println("SubController created");
		
		settings=st;
	}
	
	public void LoadForm()
	{
		prjSetName.setText(settings.getProjectName());
	}
	
	@FXML protected void actConfirmSettings(ActionEvent event)
	{
		System.out.println("Confirmed Settings");
		
		//load current information
		
		//copy data to settings
		settings.setProjectName(prjSetName.getText());
		
		System.out.println("--> "+prjSetName.getText());
		
		((Stage) prjSetConfirm.getScene().getWindow()).close();
	}
	
	@FXML protected void actCancelSettings(ActionEvent event)
	{
		System.out.println("Canceled Settings");
		
		((Stage) prjSetCancel.getScene().getWindow()).close();
		
	}
}