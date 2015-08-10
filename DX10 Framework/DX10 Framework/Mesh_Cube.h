/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Cube.h
* Description : Mesh for a Geometric Cube
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __MESH_CUBE_H__
#define __MESH_CUBE_H__

// Local Includes
#include "GeometricMesh.h"
#include "DX10Renderer.h"

class CMesh_Cube :
	public CGeometricMesh
{
public:
	/***********************
	* CMesh_Cube: Default Constructor for Mesh Cube class
	* @author: Callan Moore
	********************/
	CMesh_Cube();

	/***********************
	* ~CMesh_Cube: Default Destructor for Mesh Cube class
	* @author: Callan Moore
	********************/
	virtual ~CMesh_Cube();

	/***********************
	* Initialise: Initialise the Cube mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Cube Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, float _scale);
	
	/***********************
	* Initialise: Initialise the Cube mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Cube Mesh
	* @parameter: _color: Color for each vertex
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, float _scale, D3DXCOLOR _color);

	/***********************
	* Render: Render the Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render();
};
#endif	// __MESH_CUBE_H__

