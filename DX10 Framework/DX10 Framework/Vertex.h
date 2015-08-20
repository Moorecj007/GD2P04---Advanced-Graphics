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
	VT_COLOR,
	VT_COLOR_UV
};

/***********************
* TVertexBasic: Basic Vertex with Position only
* @author: Callan Moore
********************/
struct TVertexBasic
{
	D3DXVECTOR3 pos;
};

/***********************
* TVertexColor: Basic Vertex with Color
* @author: Callan Moore
********************/
struct TVertexColor
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
};

/***********************
* TVertexColorUV: Basic Vertex with Color and UVs
* @author: Callan Moore
********************/
struct TVertexColorUV
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
	v2float		uv;
};



#endif // __VERTEX_H__