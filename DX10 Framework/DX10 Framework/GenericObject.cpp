/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GenericObject.cpp
* Description : 3D Generic Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "GenericObject.h"

CGenericObject::CGenericObject()
{
	
}

CGenericObject::~CGenericObject()
{
	
}

void CGenericObject::BaseInitialise()
{
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
	m_pTechMatWorld = 0;
	m_pTechMatView = 0;
	m_pTechMatProj = 0;
}

bool CGenericObject::Initialise(CDX10Renderer* _pRenderer, CGenericMesh* _pMesh, D3DXCOLOR _color)
{
	// Save the Renderer and Mesh on the Object
	m_pRenderer = _pRenderer;
	m_pMesh = _pMesh;
	m_color = _color;

	// Set up the Objects for with its shaders and draw instructions
	BuildFX();
	CreateFXVarPointers();
	BuildVertexLayout();

	return true;
}

void CGenericObject::Process(float _dt)
{
	CalcWorldMatrix();
}

bool CGenericObject::BuildVertexLayout()
{
	VALIDATE(m_pRenderer->BuildVertexLayout(m_pMesh->GetVertexType(), m_techniqueID, &m_vertexLayoutID));

	return true;
}

void CGenericObject::CalcWorldMatrix()
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
	D3DXMatrixIdentity(&matTranslation);

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