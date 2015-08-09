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

// Enumerators
enum eVertexType
{
	VT_BASIC,
	VT_COLOR
};

// Basic Vertex with Position only
struct TVertexBasic
{
	D3DXVECTOR3 pos;
};

// Basic Vertex with Color
struct TVertexColor
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
};



#endif // __VERTEX_H__