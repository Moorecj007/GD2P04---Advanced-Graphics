/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GenericObject.h
* Description : 3D Generic Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GENERIC_OBJECT_H__
#define __GENERIC_OBJECT_H__

// Local Includes
#include "GenericMesh.h"

class CGenericObject
{
public:

	/***********************
	* CCube: Default Constructor for Generic Object class
	* @author: Callan Moore
	********************/
	CGenericObject();

	/***********************
	* ~CCube: Default Destructor for Generic Object class
	* @author: Callan Moore
	********************/
	~CGenericObject();

	/***********************
	* Initialise: Initialise the Generic Object for use
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for this Application
	* @parameter: _pMesh: Generic Mesh for this Object
	* @parameter: _color: Color for the Object
	* @return: bool: Successful or not
	********************/
	bool Initialise(CDX10Renderer* _pRenderer, CGenericMesh* _pMesh, D3DXCOLOR _color);
	
	/***********************
	* Process: Process the new frame and update the Generic Object
	* @author: Callan Moore
	* @parameter: _dt: The delta tick for this frame
	* @return: void
	********************/
	void Process(float _dt);
	
	/***********************
	* Draw: Draw the Generic Object to the screen space
	* @author: Callan Moore
	* @return: void
	********************/
	void Draw();
	
	/***********************
	* BuildFX: Build the FX files for the Generic Object Object
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
	
	/***********************
	* BuildVertexLayout: Build the Vertex Layout for this Object
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool BuildVertexLayout();
	
	/***********************
	* CalcWorldMatrix: Calculate the World Matrix 
	* @author: Callan Moore
	* @return: void
	********************/
	void CalcWorldMatrix();

private:
	CDX10Renderer* m_pRenderer;
	CGenericMesh* m_pMesh;
	D3DXCOLOR m_color;

	v3float m_pos;
	float m_timeElapsed;
	float m_rotationPitch;
	float m_rotationYaw;
	float m_rotationRoll;
	
	UINT m_fxID;
	UINT m_techniqueID;
	UINT m_vertexLayoutID;

	D3DXMATRIX m_matWorld;
	ID3D10EffectMatrixVariable* m_pTechMatWorld;
	ID3D10EffectMatrixVariable* m_pTechMatView;
	ID3D10EffectMatrixVariable* m_pTechMatProj;
	ID3D10EffectVectorVariable* m_pTechObjColor;
};

#endif	// __GENERIC_OBJECT_H__

