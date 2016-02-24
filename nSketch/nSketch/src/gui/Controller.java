package gui;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.text.Text;
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
		sCT = new SubController(st);
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
			// TODO Auto-generated catch block
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
	
}