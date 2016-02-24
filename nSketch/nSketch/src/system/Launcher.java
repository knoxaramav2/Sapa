package system;

import gui.Controller;
import gui.SubController;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Launcher extends Application{
	
	int defaultWidth = 1080;
	int defaultHeight = 720;

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		
		Controller CT = new Controller(new Settings(primaryStage));//primary controller
		FXMLLoader loader = new FXMLLoader(getClass().getResource("../gui/Layout.fxml"));//load primary FXML
		
		loader.setController(CT);

		loader.load();
		
		Scene scene = new Scene(loader.getRoot(),defaultWidth,defaultHeight);
		
		primaryStage.setTitle("nSketch");
		primaryStage.setScene(scene);
		primaryStage.show();
	}

}