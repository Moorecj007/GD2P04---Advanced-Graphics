/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Vertex.h
* Description : Holds all the structures for the different Vertex types
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __VERTEX_H__
#define __VERTEX_H__

// Library Includes
#include <d3dx10.h>

// Basic Vertex with Position only
struct TVertexBasic
{
	D3DXVECTOR3 pos;
};

D3D10_INPUT_ELEMENT_DESC vertexBasicDesc[] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

// Basic Vertex with Color
struct TVertexColor
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
};

D3D10_INPUT_ELEMENT_DESC vertexColorDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};



#endif // __VERTEX_H__