package system;

import java.util.ArrayList;

import javafx.stage.Stage;

class Version
{
	int MAJOR;
	int MINOR;
	int PATCH;
	
	public Version()
	{
		MAJOR=0;
		MINOR=0;
		PATCH=0;
	}
}

/*
 * Stores all project information
 * 
 */
public class Settings {

	//project information
	String projectName = null;
	Version version = null;
	Boolean activeProject = null;
	
	//system references
	Stage primaryStage = null;
	
	//file tracking
	ArrayList <String> ProjectFiles = null;
	
	public Settings(Stage stg)
	{
		projectName = new String();
		version = new Version();
		activeProject=new Boolean(false);
		
		primaryStage = stg;
	
		setProjectName("untitled");
	}
	
	public void setProjectName(String name)
	{
		projectName=name;
		
		primaryStage.setTitle("nSketch    -"+name);
		
		System.out.println("Project name set to "+name);
	}
	
	public void setVersion(int M, int m, int p)
	{
		version.MAJOR=M;
		version.MINOR=m;
		version.PATCH=p;
	}
	
	
	public String getProjectName()
	{
		return projectName;
	}

}
