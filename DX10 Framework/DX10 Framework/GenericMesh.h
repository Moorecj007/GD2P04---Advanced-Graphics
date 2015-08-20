/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GenericMesh.h
* Description : A Generic Mesh (Abstract class)
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GENERIC_MESH_H__
#define __GENERIC_MESH_H__

// Local Includes
#include "DX10Renderer.h"

class CGenericMesh
{
public:
	/***********************
	* CGeometricMesh: Default Constructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	CGenericMesh();

	/***********************
	* ~CGeometricMesh: Default Destructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	virtual ~CGenericMesh();

	/***********************
	* Initialise: Initialise the Geometric mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, v3float _scalar) = 0;

	/***********************
	* Initialise: Initialise the Geometric mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Geometric Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, v3float _scale) = 0;

	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexColorUV _vert, v3float _scale) = 0;

	/***********************
	* Render: Render the Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render() = 0;
	
	/***********************
	* GetVertexType: Retrieve the Vertex Type that the Mesh uses
	* @author: Callan Moore
	* @return: eVertexType: The Vertex Type
	********************/
	eVertexType GetVertexType()
	{
		return m_vertType;
	}

protected:
	CDX10Renderer* m_pRenderer;
	UINT m_bufferID;
	eVertexType m_vertType;
	D3D_PRIMITIVE_TOPOLOGY m_primTopology;
};

#endif	// __GENERIC_MESH_H__

