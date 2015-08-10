/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Cube.h
* Description : Mesh for a geometric Cube
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GEOMETRICMESH_CUBE_H__
#define __GEOMETRICMESH_CUBE_H__

// Local Includes
#include "DX10Renderer.h"

class CGeometricMesh
{
public:
	/***********************
	* CGeometricMesh: Default Constructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	CGeometricMesh();

	/***********************
	* ~CGeometricMesh: Default Destructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	virtual ~CGeometricMesh();

	/***********************
	* Initialise: Initialise the Cube mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Cube Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, float _scale) = 0;

	/***********************
	* Initialise: Initialise the Cube mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Cube Mesh
	* @parameter: _color: Color for each vertex
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, float _scale, D3DXCOLOR _color) = 0;

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

#endif	// __GEOMETRICMESH_CUBE_H__

