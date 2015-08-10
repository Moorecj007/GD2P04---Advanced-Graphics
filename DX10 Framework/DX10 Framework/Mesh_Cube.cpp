/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Cube.cpp
* Description : Mesh for a geometric Cube
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Mesh_Cube.h"

CMesh_Cube::CMesh_Cube()
{
}

CMesh_Cube::~CMesh_Cube()
{
}

bool CMesh_Cube::Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, float _scale)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	float vertSize = _scale / 2;
	// Create vertex buffer
	TVertexColor vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize) },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize) },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize) },

		// Left
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize) },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize) },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize) },

		// Right
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize) },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize) },

		// Back
		{ D3DXVECTOR3(vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize) },

		// Top
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize) },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize) },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize) },

		// Bottom
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize) },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize) },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize) }
	};
	m_vertType = VT_BASIC;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the Static buffer and store the ID
	m_pRenderer->CreateStaticBuffer(vertices, indices, vertexCount, indexCount, stride, &m_bufferID);

	return true;
}

bool CMesh_Cube::Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, float _scale, D3DXCOLOR _color)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	float vertSize = _scale / 2;
	// Create vertex buffer
	TVertexColor vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), _color },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), _color },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), _color },

		// Left
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), _color },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), _color },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), _color },

		// Right
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), _color },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), _color },

		// Back
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), _color },

		// Top
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), _color },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), _color },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), _color },

		// Bottom
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), _color },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), _color },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), _color }
	};
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the Static buffer and store the ID
	m_pRenderer->CreateStaticBuffer(vertices, indices, vertexCount, indexCount, stride, &m_bufferID);

	return true;
}

void CMesh_Cube::Render()
{
	m_pRenderer->SetPrimitiveTopology(m_primTopology);
	m_pRenderer->RenderMesh(m_bufferID);
}