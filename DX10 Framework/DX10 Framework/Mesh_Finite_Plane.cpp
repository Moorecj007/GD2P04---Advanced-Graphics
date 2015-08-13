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

bool CMesh_Finite_Plane::Initialise(CDX10Renderer* _pRenderer, TVertexBasic _vert, v3float _scale)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	float vertScaleX = _scale.x / 2;
	//float vertScaleY = _scale.y / 2;
	float vertScaleZ = _scale.z / 2;

	const UINT kVertexCount = 10000;
	int size = (int)sqrt(kVertexCount);
	int sizeFromOrigin = (size / 2);

	TVertexBasic vertices[kVertexCount];

	for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
	{
		for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
		{
			int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);
			vertices[index].pos = D3DXVECTOR3((width * _scale.x), 0, (length * _scale.z));
		}
	}

	// Save the information for the Vertex Buffer
	m_vertType = VT_BASIC;
	UINT stride = sizeof(*vertices);

	const UINT kIndexCount = 19800; // (size * size) + ((size - 2) * size);
	DWORD indices[kIndexCount];
	bool widthFlipDir = true;
	int index = 0;
	for (int length = -sizeFromOrigin; length < (sizeFromOrigin - 1); length++)
	{
		if (widthFlipDir == true)
		{
			for (int width = sizeFromOrigin; width > -sizeFromOrigin; width--)
			{
				indices[index++] = ((length + sizeFromOrigin) * size) + (width + sizeFromOrigin) - 1;
				indices[index++] = ((length + 1 + sizeFromOrigin) * size) + (width + sizeFromOrigin) - 1;
			}
		}
		else
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{
				indices[index++] = ((length + sizeFromOrigin) * size) + (width + sizeFromOrigin) - 1;
				indices[index++] = ((length + 1 + sizeFromOrigin) * size) + (width + sizeFromOrigin) - 1;
			}
		}

		// Flip the direction of the width loop
		widthFlipDir = !widthFlipDir;
	}

	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// Create the Static buffer and store the ID
	m_pRenderer->CreateStaticBuffer(vertices, indices, kVertexCount, kIndexCount, stride, &m_bufferID);

	return true;
}

bool CMesh_Finite_Plane::Initialise(CDX10Renderer* _pRenderer, TVertexColor _vert, v3float _scale, D3DXCOLOR _color)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	bool randomYawValues;
	_scale.y != 0.0f ? randomYawValues = true : randomYawValues = false;

	const UINT kVertexCount = 400;
	int size = (int)sqrt(kVertexCount);
	int sizeFromOrigin = (size / 2);

	TVertexColor vertices[kVertexCount];

	if (randomYawValues == true)
	{
		//float yPos = 0.0f;
		//float yBounds = 10.0f;

		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{
				//if (rand() % 2 == 1)
				//{					
				//	yPos += (float)(rand() % 10) / 100.0f;
				//	if (yPos > yBounds)
				//	{
				//		yPos = yBounds;
				//	}
				//}
				//else
				//{
				//	yPos -= (float)(rand() % 10) / 100.0f;
				//	if (yPos < -yBounds)
				//	{
				//		yPos = -yBounds;
				//	}
				//}

				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);
				//vertices[index].pos = D3DXVECTOR3((width * _scale.x), (yPos), (length * _scale.z));
				//D3DXCOLOR gradientColor = _color * ((yPos + yBounds) / 10.0f);

				float yPos = rand() % 2;
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), (yPos), (length * _scale.z));
				D3DXCOLOR gradientColor = _color * (yPos * 2.0f / 255) / 10.0f;
				vertices[index].color = gradientColor;
			}
		}
	}
	else
	{
		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{
				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), 0, (length * _scale.z));
				vertices[index].color = _color;
			}
		}
	}

	// Save the information for the Vertex Buffer
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);

	const UINT kIndexCount = 778; // (size * size) + ((size - 2) * size);
	DWORD indices[kIndexCount];
	int index = 0;
	// Cycle through all rows except last one
	for (int row = 0; row < size - 1; row++)
	{
		if (row % 2 == 0)	// Even Row
		{
			// Even Rows go Right to Left for Clockwise winding order
			for (int col = (int)(size - 1); col >= 0; col--)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = (0 + ((row + 1) * size));
			}
		}
		else	// Odd Row
		{
			// Even Rows go Left to Right for Clockwise winding order
			for (int col = 0; col < size; col++)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = ((size - 1) + ((row + 1)  * size));
			}
		}
	}

	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// Create the Static buffer and store the ID
	m_pRenderer->CreateStaticBuffer(vertices, indices, kVertexCount, kIndexCount, stride, &m_bufferID);

	return true;
}

void CMesh_Finite_Plane::Render()
{
	m_pRenderer->SetPrimitiveTopology(m_primTopology);
	m_pRenderer->RenderMesh(m_bufferID);
}