package system;

import java.io.File;

public class FileUtility {

	public static Boolean PathExists(String path)
	{
		File f = new File(path);
		return (f.exists() && f.isDirectory());
	}
	
	public static Boolean FileExists(String path)
	{
		File f = new File(path);
		return (f.exists() && !f.isDirectory());
	}
	
}
