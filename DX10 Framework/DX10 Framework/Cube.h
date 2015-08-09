/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Cube.h
* Description : 3D Cube Object
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

	
	
	/***********************
	* Initialise: Initialise the Cube for use
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for this Application
	* @return: bool: Successful or not
	********************/
	bool Initialise(CDX10Renderer* _pRenderer);
	
	/***********************
	* Process: Process the new frame and update the Cube
	* @author: Callan Moore
	* @parameter: _dt: The delta tick for this frame
	* @return: void
	********************/
	void Process(float _dt);
	
	/***********************
	* Draw: Draw the Cube to the screen space
	* @author: Callan Moore
	* @return: void
	********************/
	void Draw();
	
	/***********************
	* BuildFX: Build the FX files for the Cube Object
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool BuildFX();
	
	/***********************
	* GetFXVariable: Retrieve the FX variables from the FX file
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	virtual bool GetFXVariable();
	
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
	eVertexType m_vertexType;

	v3float m_pos;
	float m_rotationPitch;
	float m_rotationYaw;
	float m_rotationRoll;
	
	UINT m_fxID;
	UINT m_techniqueID;
	UINT m_vertexLayoutID;

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer; 
	D3DXMATRIX m_matWorld;
	ID3D10EffectVariable* m_pTechMatWorld;
	ID3D10EffectVariable* m_pTechMatView;
	ID3D10EffectVariable* m_pTechMatProj;
};

