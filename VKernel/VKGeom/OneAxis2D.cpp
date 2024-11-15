// OneAxis2D.cpp: implementation of the COneAxis2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "OneAxis2D.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class OneAxis 
//(Used for construction of revolutions and as axis of symmetries)
COneAxis2D::COneAxis2D()
{
	Position = CPoint2D(0,0);
	Direction = CVector2D(1,0);
	Direction.Normalize();
	Origin.SetParam(0,0);
	geomType = CONEAXIS2D;
}

COneAxis2D::COneAxis2D(const CPoint2D& Pos, const CVector2D& Dir) : Position(Pos), Direction(Dir)
{
	Direction.Normalize();
	Origin.SetParam(Pos.GetX(),Pos.GetY());
	geomType = CONEAXIS2D;
}

COneAxis2D::~COneAxis2D()
{
}

void COneAxis2D::SetPosition(const CPoint2D& P)
{
	Position = P;
	Origin = P;
}

void COneAxis2D::SetPosition(double x, double y)

{
	Position.SetParam(x,y);
	Origin.SetParam(x,y);
}

void COneAxis2D::SetDirection(const CVector2D& D)
{
	Direction = D;
	Direction.Normalize();
}

void COneAxis2D::SetDirection(double dx, double dy)
{
	Direction.SetParam(dx,dy);
	Direction.Normalize();
}

CPoint2D COneAxis2D::GetPosition() const
{
	return Position;
}

CVector2D COneAxis2D::GetOrigin() const
{
	return Origin;
}

CVector2D COneAxis2D::GetDirection() const
{
	return Direction;
}

bool COneAxis2D::operator == (const COneAxis2D& rhAx) const
{
	bool eq = (Position == rhAx.GetPosition() && Direction == rhAx.GetDirection()
				&& Origin == rhAx.GetOrigin());
	return eq;
}

void COneAxis2D::Translate(const COneAxis2D& Ax, const double& amt)
{
	CGeometry2D::Translate(Ax, amt);
}

void COneAxis2D::Translate(double dx, double dy)
{
	CPoint2D P = Position;
	P.Translate(dx, dy);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Translate(const CVector2D& V)
{
	CPoint2D P = Position;
	P.Translate(V);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Translate(const CPoint2D& P1, const CPoint2D& P2)
{
	CPoint2D P = Position;
	P.Translate(P1, P2);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Rotate(const CPoint2D& Ax, double ang)
{
	CPoint2D P = Position;
	CVector2D D = Direction;
	P.Rotate(Ax, ang);
	D.Rotate(Ax, ang);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Scale(const CPoint2D& Pnt, double fact)
{
	CPoint2D P = Position;
	CVector2D D = Direction;
	P.Scale(Pnt, fact);
	D.Scale(Pnt, fact);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Mirror(const CPoint2D& Pnt)
{
	CPoint2D P = Position;
	CVector2D D = Direction;
	P.Mirror(Pnt);
	D.Mirror(Pnt);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void COneAxis2D::Mirror(const COneAxis2D& Ax)
{
	CPoint2D P = Position;
	CVector2D D = Direction;
	/*CString str;
	str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	P.Mirror(Ax);
	CVector2D dir = Ax.GetDirection();
	if(dir.IsParallel(D))
		D.Mirror(Ax.GetDirection());
	else
		D.Mirror(Ax);
	/*str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

COneAxis2D COneAxis2D::OX()
{
	COneAxis2D Ax(CPoint2D(0,0), CVector2D(1,0));
	return Ax;
}

COneAxis2D COneAxis2D::OY()
{
	COneAxis2D Ax(CPoint2D(0,0), CVector2D(0,1));
	return Ax;
}

