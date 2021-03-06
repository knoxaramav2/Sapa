package gui;

import java.io.File;
import java.io.IOException;

import appFields.VersionField;
import fileIo.ProjectWriter;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;
import system.FileUtility;
import system.Settings;

public class SubController {
	
	//User mutable data
	Settings settings = null;
	Stage stage;
	
	@FXML private TextField prjSetName;
	@FXML private TextField prjPath;
	@FXML private VersionField prjVers;
	@FXML private Button prjSetCancel;
	@FXML private Button prjSetConfirm;
	@FXML private Button prjFileIO;
	@FXML private RadioButton rb1, rb2;
	
	public SubController(Settings st, Stage stg)
	{
		System.out.println("SubController created");
		
		settings=st;
		stage=stg;
		
		prjSetName = new TextField();
		prjPath = new TextField();
	}
	
	public void LoadForm()
	{
		prjSetName.setText(settings.getProjectName());
		prjPath.setText(settings.getProjectPath());
		
		if (rb1!=null)
			rb1.setSelected(true);
		if (rb2!=null)
			rb2.setSelected(false);
	}
	
	@FXML protected void actConfirmSettings(ActionEvent event)
	{
		System.out.println("Confirmed Settings");
		
		//load current information
		
		//copy data to settings
		settings.setProjectName(prjSetName.getText());
		
		System.out.println("--> "+prjSetName.getText());
		
		
		ProjectWriter.saveProject(settings);
		
		((Stage) prjSetConfirm.getScene().getWindow()).close();
	}
	
	@FXML protected void actCancelSettings(ActionEvent event)
	{
		System.out.println("Canceled Settings");
		
		((Stage) prjSetCancel.getScene().getWindow()).close();
		
	}
	
	@FXML protected void actConfirmNewProject(ActionEvent event)
	{
		System.out.println("Project Wizard Confirmation");
		
		//Validate controls
			//Verify output is unused
		System.out.println("Checking for path or file "+settings.getProjectPath()+prjSetName.getText());
		if (FileUtility.PathExists(settings.getProjectPath()+prjSetName.getText()))
		{
			//path exists
			System.out.println("Project already exists");
		}
		//Create new project files
		settings.setProjectName(prjSetName.getText());
		settings.setProjectPath(prjPath.getText());
		
		
		
		if (ProjectWriter.writeProjectFile(settings))
			settings.setProjectActive(true);
		else
			System.out.println("Project unable to be created");
		
		((Stage) prjSetConfirm.getScene().getWindow()).close();
	}
	
	@FXML protected void actCancelNewProject(ActionEvent event)
	{
		System.out.println("Canceled Settings");
		
		((Stage) prjSetCancel.getScene().getWindow()).close();
	}
	
	@FXML protected void actSelectPath(ActionEvent event)
	{
		System.out.println("Select Path");
		
		DirectoryChooser dc = new DirectoryChooser();
		
		dc.setTitle("Select Project Parent Directory");
		File pth = dc.showDialog(stage);
		
		if (pth!=null)
		{
			try {
				settings.setProjectPath(pth.getCanonicalPath());
				this.LoadForm();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
