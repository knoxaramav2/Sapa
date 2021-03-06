package gui;

import java.awt.Desktop;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import com.sun.prism.paint.Color;

import coordinate.Space3D;
import fileIo.ProjectWriter;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.DepthTest;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.PerspectiveCamera;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Material;
import javafx.scene.paint.Paint;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.MeshView;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.scene.transform.Rotate;
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
	@FXML Label xcoordLabel;
	@FXML Label ycoordLabel;
	@FXML Label xPosLabel;
	@FXML Label yPosLabel;
	@FXML Label zPosLabel;
	@FXML Label xRotLabel;
	@FXML Label yRotLabel;
	@FXML Label zRotLabel;
	@FXML BorderPane mainWindow;
	@FXML Pane centerWindow;
	
	
	public Controller(Settings st, Stage pStage)
	{
		System.out.println("Controller created");
		settings=st;
		
		//Load controls
		sCT = new SubController(st, pStage);
		stage=pStage;
		
		//centerPane.getChildren().add(new MeshView());
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
		
		Rectangle rr = new Rectangle(600,300);
		rr.setTranslateX(0);
		rr.setTranslateY(0);
		rr.setTranslateZ(10);
		rr.setFill(Paint.valueOf("RED"));
		
		Rectangle rb = new Rectangle(300,300);
		rb.setTranslateX(0);
		rb.setTranslateY(0);
		rb.setTranslateZ(20);
		rb.setFill(Paint.valueOf("BLUE"));
		
		Rectangle rg = new Rectangle(300,300);
		rg.setTranslateX(0);
		rg.setTranslateY(0);
		rg.setTranslateZ(0);
		rg.setFill(Paint.valueOf("GREEN"));
		
		Group rotGrp = new Group(rr,rg,rb);
		rotGrp.setTranslateX(0);
		rotGrp.setTranslateY(0);
		rotGrp.setRotationAxis(Rotate.Y_AXIS);
		
		Slider s = new Slider(0,360,0);
		s.setBlockIncrement(1);
		s.setTranslateX(225);
		s.setTranslateY(575);
		rotGrp.rotateProperty().bind(s.valueProperty());
		
		Group root = new Group(rotGrp,s);
		
		rotGrp.setDepthTest(DepthTest.ENABLE);
		
		
		//mainWindow.centerProperty().set(root);
		centerWindow.getChildren().add(root);
		
		//Scene scn = new Scene(root,600,600);
		//scn.setCamera(new PerspectiveCamera());
		
		//stage.setScene(scn);
		//stage.show();
		
		
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
	
	public void initializeGraphics()
	{
		
	}

	public void setStatus(String msg)
	{
		statusLabel.setText(msg);
	}

	public void setCoordLabel(double xpos, double ypos)
	{
		xcoordLabel.setText(Double.toString(xpos));
		ycoordLabel.setText(Double.toString(ypos));
	}
	
	public void setViewLabel(Space3D space)
	{
		xPosLabel.setText(Integer.toString((int)space.getXPos()));
		yPosLabel.setText(Integer.toString((int)space.getYPos()));
		zPosLabel.setText(Integer.toString((int)space.getZPos()));
		
		xRotLabel.setText(Integer.toString((int)space.getXAngle()));
		yRotLabel.setText(Integer.toString((int)space.getYAngle()));
		zRotLabel.setText(Integer.toString((int)space.getZAngle()));
	}
}