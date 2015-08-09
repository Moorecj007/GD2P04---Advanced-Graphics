/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Cube.cpp
* Description : 3D Cube Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Cube.h"

CCube::CCube()
{
	// Set the Vertex Type the Cube will use
	m_vertexType = VT_COLOR;

	// Set initial position to origin point
	m_pos = { 0, 0, 0 };

	// Initialise Rotations to zero
	m_rotationPitch = 0;
	m_rotationYaw = 0;
	m_rotationRoll = 0;

	// Set IDs to zero (Invalid ID)
	m_techniqueID = 0;
	m_fxID = 0;
	m_vertexLayoutID = 0;

	// Set all pointers to NULL
	m_pRenderer = 0;
	m_pVertexBuffer = 0;
	m_pIndexBuffer = 0;
	m_pTechMatWorld = 0;
	m_pTechMatView = 0;
	m_pTechMatProj = 0;
}

CCube::~CCube()
{
	ReleaseCOM(m_pIndexBuffer);
	ReleaseCOM(m_pVertexBuffer);

	ReleasePtr(m_pTechMatWorld);
	ReleasePtr(m_pTechMatView);
	ReleasePtr(m_pTechMatProj);
}

bool CCube::Initialise(CDX10Renderer* _pRenderer)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	// Set up the Cube for with its shaders and draw instructions
	BuildFX();
	GetFXVariable();
	BuildVertexLayout();

	return true;
}

void CCube::Process(float _dt)
{

}

void CCube::Draw()
{

}

bool CCube::BuildFX()
{
	VALIDATE(m_pRenderer->BuildFX("color.fx", "ColorTechnique", &m_fxID, &m_techniqueID));

	return true;
}

bool CCube::GetFXVariable()
{
	VALIDATE(m_pRenderer->GetFXVariable(m_fxID, "matColorWorld", m_pTechMatWorld));
	VALIDATE(m_pRenderer->GetFXVariable(m_fxID, "matColorView", m_pTechMatView));
	VALIDATE(m_pRenderer->GetFXVariable(m_fxID, "matColorProj", m_pTechMatProj));

	return true;
}

bool CCube::BuildVertexLayout()
{
	VALIDATE(m_pRenderer->BuildVertexLayout(m_vertexType, m_techniqueID, &m_vertexLayoutID));

	return true;
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