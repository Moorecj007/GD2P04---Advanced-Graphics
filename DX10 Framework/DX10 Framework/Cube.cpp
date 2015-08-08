/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Cube.cpp
* Description : TO DO
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Cube.h"

CCube::CCube()
{
}

CCube::~CCube()
{
}

bool CCube::BuildFX()
{
	return true;
}

bool CCube::GetFXVariable()
{
	return true;
}

bool CCube::BuildVertexLayout()
{
	return true;
}

void CCube::Process()
{

}

void CCube::Draw()
{

}

void CCube::CalcWorldMatrix()
{
	// Matrices to make up the World Matrix
	D3DXMATRIX matRotatePitch;
	D3DXMATRIX matRotateYaw;
	D3DXMATRIX matRotateRoll;
	D3DXMATRIX matTranslation;

	// Initialise each matrix to Identity
	D3DXMatrixIdentity(&matRotatePitch);
	D3DXMatrixIdentity(&matRotateYaw);
	D3DXMatrixIdentity(&matRotateRoll);

	// Reset the Objects World Matrix for new Calculation
	D3DXMatrixIdentity(&m_matWorld);

	// Calculate a Rotation Matrices around the Pitch, Yaw and Roll axes
	D3DXMatrixRotationX(&matRotatePitch, m_rotationPitch);
	D3DXMatrixRotationY(&matRotateYaw, m_rotationYaw);
	D3DXMatrixRotationZ(&matRotateRoll, m_rotationRoll);

	// Calculate the Full Rotation Matrix and store in the World Matrix
	m_matWorld = matRotatePitch * matRotateYaw * matRotateRoll;

	// Calculate a translation Matrix based on the Objects current position in world space
	D3DXMatrixTranslation(&matTranslation, m_pos.x, m_pos.y, m_pos.z);

	// Calculate the Objects World Matrix
	m_matWorld *= matTranslation;
}