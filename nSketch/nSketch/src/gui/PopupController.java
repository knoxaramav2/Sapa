package gui;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBoxBuilder;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class PopupController extends Application{
	
	Scene s1;
	Stage stage;

	PopupController()
	{
		
	}

	//Supported FXML forms
	@FXML private Label L1, L2, L3, L4, L5;
	@FXML private Button B1, B2, B3, B4, B5;
	
	@FXML private Button OK;
	@FXML private Button Cancel;
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		stage=primaryStage;
	}
	
	@FXML protected void Cancel(ActionEvent event)
	{
		((Stage) Cancel.getScene().getWindow()).close();
	}
	
	@FXML protected void Confirm(ActionEvent event)
	{
		
		((Stage) OK.getScene().getWindow()).close();
	}
	
	
}
