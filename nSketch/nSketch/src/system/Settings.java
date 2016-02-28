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
	String projectPath = null;
	Version version = null;
	Boolean activeProject = null;
	
	//Compiler Settings
	Boolean bitmode64;
	String interLang;
	
	//Biology Globals
	public Double ECSC;//extra cellular space concentration
	public Integer TDF;//time dilation factor
	
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
		setProjectPath("projects/");
	}
	
	public void setProjectName(String name)
	{
		projectName=name;
		
		primaryStage.setTitle("nSketch    - "+name);
		
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

	public Boolean isProjectActive()
	{
		return activeProject;
	}
	
	public String getProjectPath()
	{
		return projectPath;
	}
	
	public void setProjectPath(String path)
	{
		System.out.println("Settings path to "+path);
		projectPath=path;
	}
	
	public void setProjectActive(Boolean state)
	{
		activeProject=state;
	}
}
