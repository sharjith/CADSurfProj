#include "stdafx.h"
#include "GLCamera.h"
#include "math.h"

#include <iostream>
#include <windows.h>

#define SQR(x) (x*x)

#define NULL_VECTOR F3dVector(0.0f,0.0f,0.0f)

SF3dVector F3dVector ( GLdouble x, GLdouble y, GLdouble z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLdouble GetF3dVectorLength( SF3dVector * v)
{
	return (GLdouble)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

SF3dVector Normalize3dVector( SF3dVector v)
{
	SF3dVector res;
	double l = GetF3dVectorLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

SF3dVector operator+ (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
SF3dVector operator- (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


SF3dVector operator* (SF3dVector v, double r)
{
	SF3dVector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v)
{
	SF3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
double operator* (SF3dVector v, SF3dVector u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}




/***************************************************************************************/

CGLCamera::CGLCamera()
{
	ResetAll();
}

CGLCamera::~CGLCamera()
{
	/*CString str;
	str.Format(L"ViewDir = %0.3f, %0.3f, %0.3f\nRightVector = %0.3f, %0.3f, %0.3f\nUpDir = %0.3f, %0.3f, %0.3f",
		ViewDir.x, ViewDir.y, ViewDir.z,
		RightVector.x, RightVector.y, RightVector.z,
		UpVector.x, UpVector.y, UpVector.z);
	AfxMessageBox(str);*/
}


void CGLCamera::Move (SF3dVector Direction)
{
	Position = Position + Direction;
}

void CGLCamera::RotateX (GLdouble Angle)
{	
	RotatedX += Angle;

	if((RotatedX > 360) || (RotatedX < -360))
	{
		RotatedX = 0;
	}	
	
	//Rotate viewdir around the right vector:
	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
								+ UpVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;

	
}

void CGLCamera::RotateY (GLdouble Angle)
{
	RotatedY += Angle;

	if((RotatedY > 360) || (RotatedY < -360))
	{
		RotatedY = 0;
	}
	
	//Rotate viewdir around the up vector:
	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
								- RightVector*sin(Angle*PIdiv180));

	//now compute the new RightVector (by cross product)
	RightVector = CrossProduct(&ViewDir, &UpVector);
}

void CGLCamera::RotateZ (GLdouble Angle)
{
	RotatedZ += Angle;
	
	if((RotatedZ > 360) || (RotatedZ < -360))
	{
		RotatedZ = 0;
	}

	//Rotate viewdir around the right vector:
	RightVector = Normalize3dVector(RightVector*cos(Angle*PIdiv180)
								+ UpVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void CGLCamera::Render( void )
{

	//The point at which the camera looks:
	SF3dVector ViewPoint = Position+ViewDir;

	// Camera Zooming
	glScaled(ZoomValue, ZoomValue, ZoomValue);

	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				UpVector.x,UpVector.y,UpVector.z);
}

void CGLCamera::MoveForward( GLdouble Distance )
{
	Position = Position + (ViewDir*-Distance);
}

void CGLCamera::StrafeRight ( GLdouble Distance )
{
	Position = Position + (RightVector*Distance);
}

void CGLCamera::MoveUpward( GLdouble Distance )
{
	Position = Position + (UpVector*Distance);
}

void CGLCamera::SetZoom(GLdouble Factor)
{
	ZoomValue = Factor;
}

void CGLCamera::SetView(CGLCamera::ViewProjection proj)
{
	ResetAll();	
	m_ViewProj = proj;
	switch(m_ViewProj)
	{
	case TOP_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( 0.0, 0.0, -1.0);
		RightVector = F3dVector (1.0, 0.0, 0.0);
		UpVector = F3dVector (0.0, 1.0, 0.0);
		break;
	case BOTTOM_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( 0.0, 0.0, 1.0);
		RightVector = F3dVector (1.0, 0.0, 0.0);
		UpVector = F3dVector (0.0, -1.0, 0.0);
		break;
	case FRONT_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( 0.0, 1.0, 0.0);
		RightVector = F3dVector (1.0, 0.0, 0.0);
		UpVector = F3dVector (0.0, 0.0, 1.0);
		break;
	case REAR_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( 0.0, -1.0, 0.0);
		RightVector = F3dVector (-1.0, 0.0, 0.0);
		UpVector = F3dVector (0.0, 0.0, 1.0);
		break;
	case LEFT_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( -1.0, 0.0, 0.0);
		RightVector = F3dVector (0.0, 1.0, 0.0);
		UpVector = F3dVector (0.0, 0.0, 1.0);
		break;
	case RIGHT_VIEW:
		Position = F3dVector (0.0, 0.0,	0.0);
		ViewDir = F3dVector( 1.0, 0.0, 0.0);
		RightVector = F3dVector (0.0, -1.0, 0.0);
		UpVector = F3dVector (0.0, 0.0, 1.0);
		break;	
	case DIMETRIC_VIEW:		
		Position = F3dVector (0,0,0);
		ViewDir = F3dVector (-2.0, 2.0, -1);
		RightVector = F3dVector (1, 1, 0);
		UpVector = F3dVector(-1, 1, 0);
		break;
	case TRIMETRIC_VIEW:		
		Position = F3dVector (0,0,0);
		ViewDir = F3dVector (-0.486, 0.732, -0.477);
		RightVector = F3dVector (1.181, 0.778, 0.010);
		UpVector = F3dVector(-0.363, 0.568, 1.243);
		break;
	case ISOMETRIC_VIEW:
	default:		
		Position = F3dVector (0,0,0);
		ViewDir = F3dVector (-1, 1, -1);
		RightVector = F3dVector (1, 1, 0);
		UpVector = F3dVector(-1, 1, 0);
		break;
	}
}

void CGLCamera::SetPosition(SF3dVector pos)
{
	Position = pos;
}

void CGLCamera::ResetAll()
{
	//Init with standard OGL values:
	Position = F3dVector (0.0, 0.0,	0.0);
	ViewDir = F3dVector( 0.0, 0.0, -1.0);
	RightVector = F3dVector (1.0, 0.0, 0.0);
	UpVector = F3dVector (0.0, 1.0, 0.0);

	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	ZoomValue = 1.0;
}
