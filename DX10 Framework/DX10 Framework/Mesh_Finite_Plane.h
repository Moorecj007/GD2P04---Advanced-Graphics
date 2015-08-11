/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.h
* Description : The core of the Application is run here. The link between all components.
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


};
#endif	// __MESH_FINITE_PLANE_H__
