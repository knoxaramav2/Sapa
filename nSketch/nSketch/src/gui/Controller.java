package gui;

import java.awt.Desktop;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import fileIo.ProjectWriter;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import system.Settings;
import system.SysIO;

public class Controller {
	
	//Held References
	SubController sCT = null;
	
	Settings settings = null;
	Stage stage = null;
	
	@FXML Label statusLabel;
	@FXML Label actionLabel;
	
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
		SysIO.print("About", actionLabel);
		
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
		SysIO.print("Configure Project", actionLabel);
		
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
		
		SysIO.print("Exe Dev", actionLabel);
		
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
	
	@FXML protected void actSetPrj(ActionEvent event)
	{
		settings.setProjectActive(true);
		
		SysIO.print("Set Active", actionLabel);
	}
	
	@FXML protected void actNewProject(ActionEvent event)
	{
		SysIO.print("New Project", actionLabel);
		
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
		SysIO.print("Load Project", actionLabel);
		
		FileChooser fc = new FileChooser();
		fc.setTitle("Open Project File");
		fc.setInitialDirectory(new File(settings.getProjectPath()));
		
		FileChooser.ExtensionFilter filter = new FileChooser.ExtensionFilter("nSketch Project (*.cns)", "*.cns");
		fc.getExtensionFilters().add(filter);
		
		File file = fc.showOpenDialog(stage);
		if (file!=null)
		{
			loadProjectFile(file);
		} else
			return;
	}
	
	@FXML protected void actSaveProject(ActionEvent event)
	{
		SysIO.print("Save Project", actionLabel);
		
		ProjectWriter.saveProject(settings);
	}

	
	//Utility methods	
	protected void loadProjectFile(File file)
	{
		
		System.out.println(file.getName());
	}

	public void setStatus(String msg)
	{
		statusLabel.setText(msg);
	}
}