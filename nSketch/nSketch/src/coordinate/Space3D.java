package coordinate;

import javafx.scene.transform.Rotate;
import javafx.scene.transform.Scale;
import javafx.scene.transform.Translate;

public class Space3D {

	private Translate position = new Translate();
	
	private Rotate rx = new Rotate();
	private Rotate ry = new Rotate();
	private Rotate rz = new Rotate();
	
	private Scale scale = new Scale();
	
	public Space3D(double xp, double yp, double zp, double xr, double yr, double zr, Scale sc)
	{
		position.setX(xp);
		position.setY(yp);
		position.setZ(zp);
		
		rx.setAngle(xr);
		ry.setAngle(yr);
		rz.setAngle(zr);
		
		rx.setAxis(Rotate.X_AXIS);
		ry.setAxis(Rotate.Y_AXIS);
		rz.setAxis(Rotate.Z_AXIS);
		
		scale = sc;
	}
	
	public void setScale(Scale sc)
	{
		scale = sc;
	}
	
	public void setXAngle(double rot)
	{
		if (rot>360)
			rot-=360;
		else if (rot<0)
			rot+=360;
		
		rx.setAngle(rot);
	}
	
	public void setYAngle(double rot)
	{
		if (rot>360)
			rot-=360;
		else if (rot<0)
			rot+=360;
		
		ry.setAngle(rot);
	}
	
	public void setZAngle(double rot)
	{
		if (rot>360)
			rot-=360;
		else if (rot<0)
			rot+=360;
		
		rz.setAngle(rot);
	}
	
	
	public double getXAngle()
	{
		return rx.getAngle();
	}
	
	public double getYAngle()
	{
		return ry.getAngle();
	}
	
	public double getZAngle()
	{
		return rz.getAngle();
	}
	
	public double getXPos()
	{
		return position.getX();
	}
	
	public double getYPos()
	{
		return position.getY();
	}
	
	public double getZPos()
	{
		return position.getZ();
	}
}
