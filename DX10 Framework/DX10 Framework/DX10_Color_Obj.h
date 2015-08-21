/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Color_Obj.h
* Description : 3D Color Object for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_COLOR_OBJ_H__
#define __DX10_COLOR_OBJ_H__

// Local Includes
#include "GenericObject.h"

class DX10_Color_Obj :
	public CGenericObject
{
public:

	/***********************
	* DX10_Color_Obj: Default Constructor for Color Object class
	* @author: Callan Moore
	********************/
	DX10_Color_Obj();

	/***********************
	* ~DX10_Color_Obj: Default Constructor for Color Object class
	* @author: Callan Moore
	********************/
	~DX10_Color_Obj();

	/***********************
	* Draw: Draw the Color Object to the screen space
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Draw();

	/***********************
	* BuildFX: Build the FX files for the Color Object
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool BuildFX();

	/***********************
	* CreateFXVarPointers: Retrieve the FX variables from the FX file
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool CreateFXVarPointers();
};

#endif	// __DX10_COLOR_OBJ_H__

