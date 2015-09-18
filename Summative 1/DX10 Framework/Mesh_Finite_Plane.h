/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Finite_Plane.h
* Description : Creates a Mesh for a Finite Plane
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __MESH_FINITE_PLANE_H__
#define __MESH_FINITE_PLANE_H__

// Local Includes
#include "GeometricMesh.h"

class CMesh_Finite_Plane :
	public CGeometricMesh
{
public:

	/***********************
	* CMesh_Finite_Plane: Default Constructor for Finite Plane Mesh class
	* @author: Callan Moore
	********************/
	CMesh_Finite_Plane();

	/***********************
	* ~CMesh_Finite_Plane: Default Destructor for Finite Plane Mesh class
	* @author: Callan Moore
	********************/
	~CMesh_Finite_Plane();

	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, v3float _scale);

	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @parameter: _color: Color for each vertex
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, v3float _scale, D3DXCOLOR _color);

	/***********************
	* Render: Render the finite plane Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render();


};
#endif	// __MESH_FINITE_PLANE_H__
