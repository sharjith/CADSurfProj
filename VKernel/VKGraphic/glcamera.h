//***************************************************************************
//
// Advanced CodeColony Camera
// Philipp Crocoll, 2003
//
//***************************************************************************


#include <GL\gl.h>
#include <GL\glu.h>

#include "VKGraphic.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#define PIdiv180 (PI/180.0)

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct VKGRAPHIC_API SF3dVector  //Float 3d-vect, normally used
{
	GLdouble x,y,z;
};
struct VKGRAPHIC_API SF2dVector
{
	GLdouble x,y;
};
VKGRAPHIC_API SF3dVector F3dVector ( GLdouble x, GLdouble y, GLdouble z );

class VKGRAPHIC_API CGLCamera
{
public:
	enum ViewProjection
	{
		TOP_VIEW,
		BOTTOM_VIEW,
		FRONT_VIEW,
		REAR_VIEW,
		LEFT_VIEW,
		RIGHT_VIEW,
		ISOMETRIC_VIEW,
		DIMETRIC_VIEW,
		TRIMETRIC_VIEW
	};

private:
	
	SF3dVector ViewDir;
	SF3dVector RightVector;	
	SF3dVector UpVector;
	SF3dVector Position;

	GLdouble RotatedX, RotatedY, RotatedZ, ZoomValue;	
	ViewProjection m_ViewProj;
	
public:
	CGLCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	~CGLCamera();
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render

	void Move ( SF3dVector Direction );
	void RotateX ( GLdouble Angle );
	void RotateY ( GLdouble Angle );
	void RotateZ ( GLdouble Angle );	

	void MoveForward ( GLdouble Distance );
	void MoveUpward ( GLdouble Distance );
	void StrafeRight ( GLdouble Distance );

	void SetZoom(GLdouble Factor);
	void SetView(CGLCamera::ViewProjection proj);
	void SetPosition(SF3dVector pos);
	void ResetAll();

};


