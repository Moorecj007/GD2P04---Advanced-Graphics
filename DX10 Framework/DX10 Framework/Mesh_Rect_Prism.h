/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Rect_Prism.h
* Description : Mesh for a Geometric Rectangular Prism
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __MESH_RECT_PRISM_H__
#define __MESH_RECT_PRISM_H__

// Local Includes
#include "GeometricMesh.h"
#include "DX10Renderer.h"

class CMesh_Rect_Prism :
	public CGeometricMesh
{
public:
	/***********************
	* CMesh_Rect_Prism: Default Constructor for Mesh Rect Prism class
	* @author: Callan Moore
	********************/
	CMesh_Rect_Prism();

	/***********************
	* ~CMesh_Rect_Prism: Default Destructor for Mesh Rect Prism class
	* @author: Callan Moore
	********************/
	virtual ~CMesh_Rect_Prism();

	/***********************
	* Initialise: Initialise the Rect Prism mesh
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
	* Render: Render the Rect Prism Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render();
};
#endif	// __MESH_RECT_PRISM_H__

