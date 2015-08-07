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

class CGeometricObject
{
public:
	/***********************
	* ~CGeometricObject: Default Constructor for Geometric Object class
	* @author: Callan Moore
	********************/
	CGeometricObject();

	/***********************
	* ~CGeometricObject: Default Destructor for Geometric Object class
	* @author: Callan Moore
	********************/
	virtual ~CGeometricObject();

};

#endif // __GEOMETRICOBJECT_H__

