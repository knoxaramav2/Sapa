package system;

import java.io.File;

public class FileUtility {

	public static Boolean PathExists(String path)
	{
		return !((new File(path))==null);
	}
	
}
