package system;

import coordinate.Space3D;
import gui.Controller;
import javafx.application.Application;
import javafx.application.ConditionalFeature;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.PerspectiveCamera;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.scene.transform.Scale;
import javafx.stage.Stage;

public class Launcher extends Application{
	
	int defaultWidth = 1080;
	int defaultHeight = 720;
	
	//Orientation and Positions
	PerspectiveCamera cam;
	
	Space3D space;
	
	double mouseX = 0;
	double mouseY = 0;

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		
		if (!Platform.isSupported(ConditionalFeature.SCENE3D))
		{
			throw new RuntimeException("SCENE3D not supported\n");
		}
		
		//setup motion control
		space = new Space3D(0,0,0,0,0,0,new Scale(0,0,0));
		
		Controller CT = new Controller(new Settings(primaryStage), primaryStage);//primary controller
		FXMLLoader loader = new FXMLLoader(getClass().getResource("../gui/Layout.fxml"));//load primary FXML
		
		loader.setController(CT);
		
		loader.load();
		CT.initializeGraphics();
		
	
		Scene scene = new Scene(loader.getRoot(),defaultWidth,defaultHeight,true);
		cam = new PerspectiveCamera();
		scene.setCamera(cam);
		
		primaryStage.setScene(scene);
		primaryStage.show();

		scene.setOnMouseDragged(new EventHandler<MouseEvent>()
		{	
			@Override
			public void handle(MouseEvent event) {
				
				double dX = mouseX-event.getX();
				double dY = mouseY-event.getY();
				
				mouseX=event.getX();
				mouseY=event.getY();
				
				if (event.isShiftDown() && event.isPrimaryButtonDown())
				{
					System.out.println("Dragged");
					space.setXAngle(space.getXAngle()+dY);
					space.setYAngle(space.getYAngle()-dX);
				}
				
				CT.setCoordLabel(mouseX, mouseY);
				CT.setViewLabel(space);
			}
			
		});
		
		scene.setOnMouseMoved(new EventHandler<MouseEvent>()
		{

			@Override
			public void handle(MouseEvent event) {
				mouseX=event.getX();
				mouseY=event.getY();
				
				CT.setCoordLabel(mouseX, mouseY);
				CT.setViewLabel(space);
			}
		});
	}
}