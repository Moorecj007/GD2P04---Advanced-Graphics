/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GeometricObject.h
* Description : Abstract class to base all Geometric objects from and hold shared functionality
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GEOMETRICOBJECT_H__
#define __GEOMETRICOBJECT_H__

// TO DO MOVE TO ANOTHER LOCATION/ DeLEETE REFERENCE
typedef unsigned int UINT;
#include <d3d10.h>
#include <d3dx10.h>

// Local Includes
#include "DX10Renderer.h"

class CGeometricObject
{
public:
	/***********************
	* CGeometricObject: Default Constructor for Geometric Object class
	* @author: Callan Moore
	********************/
	CGeometricObject();

	/***********************
	* ~CGeometricObject: Default Destructor for Geometric Object class
	* @author: Callan Moore
	********************/
	virtual ~CGeometricObject();

	virtual bool BuildFX() = 0;
	virtual bool GetFXVariable() = 0;
	virtual bool BuildVertexLayout() = 0;





private:



};

#endif // __GEOMETRICOBJECT_H__

