/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : StaticBuffer.cpp
* Description : Wrapper class to hold all information for Vertex and Index Buffers for use in DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "StaticBuffer.h"

CStaticBuffer::CStaticBuffer(ID3D10Device* _pDX10Device)
{
	m_pDX10Device = _pDX10Device;
}

CStaticBuffer::~CStaticBuffer()
{
	ReleaseCOM(m_pVertexBuffer);
	ReleaseCOM(m_pIndexBuffer);
}

void CStaticBuffer::Render()
{
	UINT offset = 0;
	m_pDX10Device->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_stride, &offset);
	m_pDX10Device->IASetIndexBuffer(m_pIndexBuffer, m_indexFormat, 0);
	m_pDX10Device->DrawIndexed(m_indexCount, 0, 0);
}
