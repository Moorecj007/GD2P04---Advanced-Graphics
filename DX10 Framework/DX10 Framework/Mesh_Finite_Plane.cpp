/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Finite_Plane.cpp
* Description : Creates a Mesh for a Finite Plane
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Mesh_Finite_Plane.h"

CMesh_Finite_Plane::CMesh_Finite_Plane()
{
}

CMesh_Finite_Plane::~CMesh_Finite_Plane()
{
}


void CMesh_Finite_Plane::Render()
{
	m_pRenderer->SetPrimitiveTopology(m_primTopology);
	m_pRenderer->RenderMesh(m_bufferID);
}