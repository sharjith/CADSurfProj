// ListNodeOfCPoint3D.cpp: implementation of the CListNodeOfCPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfCPoint3D.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfCPoint3D::CListNodeOfCPoint3D( const CPoint3D& P) : data(P), nextPtr(0)
{

}

CListNodeOfCPoint3D::~CListNodeOfCPoint3D()
{

}

CPoint3D CListNodeOfCPoint3D::GetData() const
{
	return data;
}

bool CListNodeOfCPoint3D::operator==(CListNodeOfCPoint3D& rhs)
{
	if(data == rhs.data)
		return true;
	return false;
}

bool CListNodeOfCPoint3D::operator!=(CListNodeOfCPoint3D& rhs)
{
	return !(*this==rhs);
}
