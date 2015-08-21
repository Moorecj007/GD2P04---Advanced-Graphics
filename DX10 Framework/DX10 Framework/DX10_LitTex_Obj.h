/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_LitTex_Obj.h
* Description : 3D Lit Texture Object for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_LITTEX_OBJ_H__
#define __DX10_LITTEX_OBJ_H__

// Local Includes
#include "GenericObject.h"

class CDX10_LitTex_Obj :
	public CGenericObject
{
public:

	/***********************
	* CDX10_LitTex_Obj: Default Constructor for Lit Texture Object class
	* @author: Callan Moore
	********************/
	CDX10_LitTex_Obj();

	/***********************
	* ~CDX10_LitTex_Obj: Default Destructor for Lit Texture Object class
	* @author: Callan Moore
	********************/
	~CDX10_LitTex_Obj();

	/***********************
	* Draw: Draw the Lit Texture Object to the screen space
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Draw();

	/***********************
	* BuildFX: Build the FX files for the Lit Texture Object
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
#endif	// __DX10_LITTEX_OBJ_H__
