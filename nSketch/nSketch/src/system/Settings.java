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
	
	@Override
	public
	String toString()
	{
		return new String(Integer.toString(MAJOR)+"."+Integer.toString(MINOR)+"."+Integer.toString(PATCH));
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
	ArrayList <String> fileList = null;
	
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
		projectPath = new String();
		version = new Version();
		activeProject=new Boolean(false);
		fileList = new ArrayList <String>();
		
		bitmode64 = new Boolean(true);
		interLang = new String("C");
		
		ECSC = new Double(0.0);
		TDF = new Integer(1);
		
		primaryStage = stg;
	
		setProjectName("untitled");
		setProjectPath("projects/");
	}
	
	public void setProjectName(String name)
	{
		projectName=name;
		
		projectPath=new String(projectPath+projectName);
		
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
	
	public String getPath()
	{
		return new String(projectPath+projectName+"/");
	}

	public String getVersion()
	{
		return version.toString();
	}
	
	public String getInterLang()
	{
		return interLang;
	}
	
	public ArrayList<String> getFileList()
	{
		return fileList;
	}
	
	public Boolean is64bit()
	{
		return bitmode64;
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
