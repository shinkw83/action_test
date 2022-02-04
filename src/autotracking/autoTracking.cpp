#include "autoTracking.h"

autoTracking::autoTracking()
{
}

autoTracking::~autoTracking()
{

}

void autoTracking::show_val()
{
	cout<<"PAN:"<<m_pan_val<<"TILT:"<<m_tilt_val<<"\n";
}


void  autoTracking::calDistance(double x, double y, double z)
{
        double distance = ((x-0)*(x-0))+((y-0)*(y-0))+((z-0)*(z-0));
	double rdistance = sqrt(distance);
        double zoomVal = 0;
        if ((rdistance/10) == 2)
        {
                zoomVal = (rdistance/10)*0.05;
        }
        else if((rdistance/10) == 4)
        {
                zoomVal = (rdistance/10)*0.1;
        }
        else if((rdistance/10) == 6)
        {
                zoomVal = (rdistance/10)*0.15;
        }
        else if((rdistance/10) == 8)
        {
                zoomVal = (rdistance/10)*0.2;
        }
        else if((rdistance/10) == 10)
        {
                zoomVal = (rdistance/10)*0.25;
        }
        else
        {
                zoomVal = 0.0;
        }
        m_distance =  zoomVal;
}


void autoTracking::auto_tracking (double r_x, double r_y, double r_z)
{
	// RDDAR  X,Y,Z real time data 
        // CAMERA X,Y,Z location
	// camera higher than lidar - distance and lower than lidar + distance 
	//rotation(r_x,r_y,m_camera_degree);
	//double rotation =0; 
	//rotation = m_camera_degree/H_CAMERA_DEGREE *0.1;
	// left < 0 rightn > 0
	
	m_x_pos = r_x + m_cameraX;
	m_y_pos = r_y + m_cameraY;
	m_z_pos = r_z + m_cameraZ;

	m_x_pos = m_x_pos *-1; 
	//m_y_pos;
	rect_to_polar(m_x_pos,m_y_pos,m_z_pos);
	//calDistance(m_x_pos,m_y_pos,m_z_pos);
	double pan_radval = m_pan_angle *Rad_to_deg;

	
	if(m_x_pos >0 && m_y_pos>0)
	{
		m_pan_val = ((90-pan_radval)/H_CAMERA_DEGREE) *0.1;
	}
	else if(m_x_pos<0 && m_y_pos>0)
	{
		m_pan_val = ((90-pan_radval)/H_CAMERA_DEGREE) *-0.1;
	}
	else if(m_x_pos<0 && m_y_pos<0)
	{
		m_pan_val = ((180+((pan_radval)+90))/H_CAMERA_DEGREE) *-0.1;
	}
	else if(m_x_pos>0 && m_y_pos<0)
	{
		m_pan_val = (((pan_radval)-90)/H_CAMERA_DEGREE) *-0.1;
	}
	
	m_pan_val=m_pan_val*-1;
	
	//m_pan_val = m_pan_val + rotation;
	/*if(r_z<=0)
	{
		if(m_camera_type ==0)
		{
			m_tilt_val = m_tilt_angle*Rad_to_deg;
			m_tilt_val = (m_tilt_val/XNP6550V_CAMERA_DEGREE) *-0.1;
			m_tilt_val = HW_TILT_VALUE+m_tilt_val;
		}
		else if(m_camera_type == 1)
		{
			m_tilt_val = m_tilt_angle*Rad_to_deg;
			m_tilt_val = (m_tilt_val/XNP6330V_CAMERA_DEGREE) *-0.1;
			m_tilt_val = HW_TILT_VALUE+m_tilt_val;

		}
		else
		{
			m_tilt_val = m_tilt_angle*Rad_to_deg;
			m_tilt_val = (m_tilt_val/AXIS_A6155) *-0.1;
			m_tilt_val = HW_TILT_VALUE+m_tilt_val;
		}
	}
	else if(r_z>0)
	{
		m_tilt_val = -1;
	}*/

}


void autoTracking::rect_to_polar(double realtime_x,double realtime_y, double realtime_z)
{
	m_pan_angle = atan2(realtime_y,realtime_x);
	if(realtime_y < 0)
	{
		realtime_y = realtime_y *-1;
	}
	m_tilt_angle = atan2(realtime_z , realtime_y);
	m_tilt_val = m_tilt_angle*Rad_to_deg;
	m_tilt_val = (m_tilt_val/5.5) *-0.1;
	
	//m_tilt_val = -0.124;
	m_tilt_val = 0.324;
}


void autoTracking::rotation(double x, double y,double degree)
{
	double r_x =0; 
	r_x= x*cos(degree)-y*sin(degree);
	double r_y=0; 
	r_y = x*sin(degree)+y*cos(degree);
}

void autoTracking::rotation_yaw(double yaw)
{
	double cal_yaw; 
	if(yaw <0)
	{
		cal_yaw = yaw /H_CAMERA_DEGREE * - 0.1;
	}
	else if(yaw >0)
	{
		cal_yaw = yaw /H_CAMERA_DEGREE * 0.1;
	}
	else
	{
		cal_yaw = m_tilt_val;
	}
	m_tilt_val = cal_yaw; 
}
