/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Cube.h
* Description : TO DO
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once
#include "GeometricObject.h"
class CCube :
	public CGeometricObject
{
public:

	/***********************
	* CCube: Default Constructor for Cube class
	* @author: Callan Moore
	********************/
	CCube();

	/***********************
	* ~CCube: Default Destructor for Cube class
	* @author: Callan Moore
	********************/
	~CCube();

	// TO DO
	virtual bool BuildFX();
	virtual bool GetFXVariable();
	virtual bool BuildVertexLayout();
	void Process();
	void Draw();
	void CalcWorldMatrix();


// TO DO - change to private
public:
	CDX10Renderer* m_pRenderer;

	v3float m_pos;
	float m_rotationPitch;
	float m_rotationYaw;
	float m_rotationRoll;
	
	UINT m_techniqueID;
	UINT m_fxID;
	UINT m_inputLayerID;

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer; 
	D3DXMATRIX m_matWorld;
};

