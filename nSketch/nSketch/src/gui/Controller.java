package gui;

import java.awt.Desktop;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import system.Settings;

public class Controller {
	
	//Held References
	SubController sCT = null;
	
	Settings settings = null;
	Stage stage = null;
	
	public Controller(Settings st, Stage pStage)
	{
		System.out.println("Controller created");
		settings=st;
		
		//Load controls
		sCT = new SubController(st, pStage);
		stage=pStage;
	}


	@FXML private Text actionTarget;
	
	@FXML protected void actAbout(ActionEvent event)
	{
		System.out.println("About Pressed");
		
		try {
			FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("About.fxml"));
			Parent root = (Parent) fxmlLoader.load();
			Stage stage = new Stage();
			stage.initModality(Modality.APPLICATION_MODAL);
			stage.setTitle("About");
			stage.setScene(new Scene(root));
			stage.show();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@FXML protected void actExit(ActionEvent event)
	{
		System.exit(0);
	}
	
	@FXML protected void actProjectSettings(ActionEvent event)
	{	
		System.out.println("Configure Project");
		
		if (!settings.isProjectActive())
			return;
		
		try {
			FXMLLoader prjLoader = new FXMLLoader(getClass().getResource("../gui/ProjectSettings.fxml"));//load project settings XML
			prjLoader.setController(sCT);
			Parent root = (Parent) prjLoader.load();
			sCT.LoadForm();
			Stage stage = new Stage();
			stage.initModality(Modality.APPLICATION_MODAL);
			stage.setTitle("Project Settings");
			stage.setScene(new Scene(root));
			stage.show();
		} catch (IOException e) {
			System.out.println("Failed to open configure dialog");
			e.printStackTrace();
		}
	}
	
	@FXML protected void actDev(ActionEvent event)
	{
		
		try {
			FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("Popup.fxml"));
			Parent root = (Parent) fxmlLoader.load();
			Stage stage = new Stage();
			stage.initModality(Modality.APPLICATION_MODAL);
			stage.setTitle("About");
			stage.setScene(new Scene(root));
			stage.show();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@FXML protected void actNewProject(ActionEvent event)
	{
		System.out.println("New Project");
		
		//prompt for save or cancel
		if (settings.isProjectActive())
		{
			
		}
		
		try {
			FXMLLoader npWizard = new FXMLLoader(getClass().getResource("../gui/NewProject.fxml"));//new Project Wizard
			npWizard.setController(sCT);
			Parent root = (Parent) npWizard.load();
			sCT.LoadForm();
			Stage stage = new Stage();
			stage.initModality(Modality.APPLICATION_MODAL);
			stage.setTitle("Project Wizard");
			stage.setScene(new Scene(root));
			stage.show();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@FXML protected void actLoadProject(ActionEvent event)
	{
		System.out.println("Load Project");
		
		FileChooser fc = new FileChooser();
		fc.setTitle("Open Project File");
		fc.setInitialDirectory(new File(settings.getProjectPath()));
		
		File file = fc.showOpenDialog(stage);
		if (file!=null)
		{
			loadProjectFile(file);
		} else
			return;
	}
	
	@FXML protected void actSaveProject(ActionEvent event)
	{
		System.out.println("Save Project");
	}
	
	
	
	//Utility methods
	
	protected void loadProjectFile(File file)
	{
		
		System.out.println(file.getName());
	}
}