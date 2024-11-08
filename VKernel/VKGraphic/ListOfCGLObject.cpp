// ListOfCGLObject.cpp: implementation of the CListOfCGLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListOfCGLObject.h"
#include "ListIteratorOfListOfCGLObject.h"
#include "ListException.h"
#include <MMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfCGLObject::CListOfCGLObject() : firstPtr(0), lastPtr(0)
{
}


CListOfCGLObject::~CListOfCGLObject()
{
	CListNodeOfCGLObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void CListOfCGLObject::Append( CGLObject* data)
{
	CListNodeOfCGLObject* newPtr = new CListNodeOfCGLObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

}


void CListOfCGLObject::Prepend( CGLObject* data)
{
	CListNodeOfCGLObject* newPtr = new CListNodeOfCGLObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

CGLObject* CListOfCGLObject::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

CGLObject* CListOfCGLObject::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}


CListNodeOfCGLObject* CListOfCGLObject::Previous(const CGLObject* O)
{
	CListIteratorOfListOfCGLObject it(this);
	for(it.Init(); it.More(); it.Next())
	{
		if(O == it.CurrentPtr()->nextPtr->data)
			break;
	}
	return it.CurrentPtr();
}

CGLObject* CListOfCGLObject::Remove(const CGLObject* O)
{
	if(IsEmpty())
		return 0;
	CGLObject* rO = 0;
	CListNodeOfCGLObject* tmp = 0;
	if(O == First())
	{
		tmp = firstPtr;
		firstPtr = firstPtr->nextPtr;
		rO = tmp->data;
	}
	else
	{
		CListNodeOfCGLObject* p = Previous(O);
		if(p->nextPtr != NULL)
		{
			tmp = p->nextPtr;
			p->nextPtr = p->nextPtr->nextPtr;
			rO = tmp->data;
		}
	}
	tmp->data = 0;
	delete tmp->data;
	delete tmp;
	return rO;
}

bool CListOfCGLObject::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfCGLObject::Clear()
{
	CListNodeOfCGLObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
}

CListNodeOfCGLObject* CListOfCGLObject::NewNode(CGLObject* P)
{
	CListNodeOfCGLObject* newPtr= new CListNodeOfCGLObject(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
