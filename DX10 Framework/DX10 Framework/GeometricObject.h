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

// macros
typedef unsigned int UINT;

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

	/***********************
	* BuildFX: Build the FX files for the Geometric Object
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool BuildFX() = 0;

	/***********************
	* GetFXVariable: Retrieve the FX variables from the FX file
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool GetFXVariable() = 0;

	/***********************
	* BuildVertexLayout: Build the Vertex Layout for the Geometric Object
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool BuildVertexLayout() = 0;

private:



};

#endif // __GEOMETRICOBJECT_H__

