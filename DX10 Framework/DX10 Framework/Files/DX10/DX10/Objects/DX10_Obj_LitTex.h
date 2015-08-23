/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Obj_LitTex.h
* Description : 3D Lit Texture Object for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_OBJ_LITTEX_H__
#define __DX10_OBJ_LITTEX_H__

// Local Includes
#include "DX10_Obj_Generic.h"

class DX10_Obj_LitTex :
	public DX10_Obj_Generic
{
public:

	/***********************
	* CDX10_LitTex_Obj: Default Constructor for Lit Texture Object class
	* @author: Callan Moore
	********************/
	DX10_Obj_LitTex();

	/***********************
	* ~CDX10_LitTex_Obj: Default Destructor for Lit Texture Object class
	* @author: Callan Moore
	********************/
	~DX10_Obj_LitTex();

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

	// TO DO
	virtual SetTexture(std::string _fileName)

private:

};
#endif	// __DX10_OBJ_LITTEX_H__
