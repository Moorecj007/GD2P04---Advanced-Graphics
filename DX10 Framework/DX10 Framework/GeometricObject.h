/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GeometricObject.h
* Description : 3D Geometric Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GEOMETRICOBJECT_H__
#define __GEOMETRICOBJECT_H__

// Local Includes
#include "GeometricMesh.h"

class CGeometricObject
{
public:

	/***********************
	* CCube: Default Constructor for Geometric Object class
	* @author: Callan Moore
	********************/
	CGeometricObject();

	/***********************
	* ~CCube: Default Destructor for Geometric Object class
	* @author: Callan Moore
	********************/
	~CGeometricObject();

	/***********************
	* Initialise: Initialise the Geometric Object for use
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for this Application
	* @parameter: _pMesh: Geometric Mesh for this Object
	* @return: bool: Successful or not
	********************/
	bool Initialise(CDX10Renderer* _pRenderer, CGeometricMesh* _pMesh);
	
	/***********************
	* Process: Process the new frame and update the Geometric Object
	* @author: Callan Moore
	* @parameter: _dt: The delta tick for this frame
	* @return: void
	********************/
	void Process(float _dt);
	
	/***********************
	* Draw: Draw the Geometric Object to the screen space
	* @author: Callan Moore
	* @return: void
	********************/
	void Draw();
	
	/***********************
	* BuildFX: Build the FX files for the Geometric Object Object
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
	CGeometricMesh* m_pMesh;

	v3float m_pos;
	float m_rotationPitch;
	float m_rotationYaw;
	float m_rotationRoll;
	
	UINT m_fxID;
	UINT m_techniqueID;
	UINT m_vertexLayoutID;

	D3DXMATRIX m_matWorld;
	ID3D10EffectVariable* m_pTechMatWorld;
	ID3D10EffectVariable* m_pTechMatView;
	ID3D10EffectVariable* m_pTechMatProj;
};

#endif	// __GEOMETRICOBJECT_H__

