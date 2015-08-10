/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Mesh_Cube.h
* Description : Basic Cube Mesh
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __MESH_CUBE_H__
#define __MESH_CUBE_H__

// Local Includes
#include "DX10Renderer.h"


class CMesh_Cube
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
	~CMesh_Cube();

	// TO DO
	template <typename TVertexType>
	bool Initialise(CDX10Renderer* _pRenderer, typename TVertexType _vertexType, float _scale)
	{
		// Save the renderer on the Cube
		m_pRenderer = _pRenderer;

		// Scale the Mesh
		float vertSize = 1.0f * _scale / 2;

		// Create vertex buffer
		TVertexType vertices[] =
		{
			// Front
			{ D3DXVECTOR3(-vertSize, vertSize, -vertSize) },
			{ D3DXVECTOR3(vertSize, vertSize, -vertSize)  },
			{ D3DXVECTOR3(vertSize, -vertSize, -vertSize)  },
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
		m_stride = sizeof(*vertices);
		m_vertexCount = (sizeof(vertices) / m_stride);


		m_pIndices = new  DWORD[] {
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

		m_indexCount = 36;//(sizeof(indices) / sizeof(*indices));

		m_pVertices = reinterpret_cast<void*>(vertices);

		return true;
	}

	// TO DO
	template <typename TVertexType>
	void UpdateColor(typename TVertexType _vertType, D3DXCOLOR _color)
	{
		TVertexType* pVertices = reinterpret_cast<TVertexType*>(m_pVertices);

		for (UINT i = 0; i < m_vertexCount-1; i++)
		{
			pVertices[i].color = _color;
		}
	}

	// TO DO - another time
	void UpdateNormals();
	void UpdateUVs();

	// TO DO
	template <typename TVertexType>
	void FinaliseMesh(typename TVertexType _vertType)
	{
		TVertexType* pVertices = reinterpret_cast<TVertexType*>(m_pVertices);

		m_pRenderer->CreateStaticBuffer(pVertices, m_pIndices, m_vertexCount, m_indexCount, m_stride, &m_bufferID);
	}

	// TO DO
	void Render()
	{
		m_pRenderer->RenderObject(m_bufferID);
	}

private:
	CDX10Renderer* m_pRenderer;
	void* m_pVertices;
	DWORD* m_pIndices;

	UINT m_stride;
	UINT m_vertexCount;
	UINT m_indexCount;
	UINT m_bufferID;
};
#endif	// __MESH_CUBE_H__

