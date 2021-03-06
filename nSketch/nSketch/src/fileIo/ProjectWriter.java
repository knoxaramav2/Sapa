package fileIo;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

import system.FileUtility;
import system.Settings;

public class ProjectWriter {

	//write project description file
	public static Boolean writeProjectFile(Settings stt)
	{	
		if (!FileUtility.PathExists(stt.getProjectPath()+stt.getProjectName()))
			try {
				//create new project path and file
				(new File(stt.getProjectPath()+stt.getProjectName())).mkdir();
				File prjFile = new File(stt.getPath()+"/"+stt.getProjectName()+".cns");
				prjFile.createNewFile();
				System.out.println("Created new project");
			} catch (IOException e) {
				System.out.println("Failed to create project");
				e.printStackTrace();
				return false;
			}
		
		try {
			PrintWriter writer = new PrintWriter(stt.getPath()+"/"+stt.getProjectName()+".cns", "UTF-8");
			//Write file************************
			writer.println("title="+stt.getProjectName());
			writer.println("version="+stt.getVersion());
			writer.print("files=");
			for (String s: stt.getFileList())
				writer.print(s+" ");
			writer.println();
			writer.println("bitmode="+stt.is64bit().toString());
			writer.println("interlang="+stt.getInterLang());
			//**********************************
			writer.close();
			System.out.println("Project file write complete");
		} catch (FileNotFoundException e) {
			System.out.println("Write failure");
			e.printStackTrace();
			return false;
		} catch (UnsupportedEncodingException e) {
			System.out.println("Write failure");
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
	
	public static Boolean readProjectFile(Settings stt)
	{
		return true;
	}
	
	//write/save particular source file
	public static Boolean writeNeuronFile(Settings stt, String target)
	{
		
		
		return true;
	}
	
	public static Boolean readNeuroNFile(Settings stt, String target)
	{
		
		return true;
	}
	
	//save entire project
	public static Boolean saveProject(Settings stt)
	{
		writeProjectFile(stt);
		
		
		
		return true;
	}
	
	//load entire project
	public static Boolean loadProject(Settings stt)
	{
		
		return true;
	}
}
