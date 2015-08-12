/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GeometricObject.cpp
* Description : 3D Geometric Object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "GeometricObject.h"

CGeometricObject::CGeometricObject()
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

CGeometricObject::~CGeometricObject()
{
	
}

bool CGeometricObject::Initialise(CDX10Renderer* _pRenderer, CGeometricMesh* _pMesh)
{
	// Save the Renderer and Mesh on the Object
	m_pRenderer = _pRenderer;
	m_pMesh = _pMesh;

	// Set up the Cube for with its shaders and draw instructions
	BuildFX();
	CreateFXVarPointers();
	BuildVertexLayout();

	return true;
}

void CGeometricObject::Process(float _dt)
{
	//m_rotationYaw += (float)D3DXToRadian(60.0f) * _dt;
}

void CGeometricObject::Draw()
{
	m_pRenderer->RestoreDefaultDrawStates();
	m_pRenderer->SetInputLayout(m_vertexLayoutID);
	ID3D10EffectTechnique* pTech = m_pRenderer->GetTechnique(m_techniqueID);

	if (pTech != NULL)
	{
		D3D10_TECHNIQUE_DESC techDesc;
		pTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			CalcWorldMatrix();
			m_pTechMatWorld->AsMatrix()->SetMatrix((float*)m_matWorld);
			m_pTechMatView->AsMatrix()->SetMatrix((float*)*m_pRenderer->GetViewMatrix());
			m_pTechMatProj->AsMatrix()->SetMatrix((float*)*m_pRenderer->GetProjMatrix());

			pTech->GetPassByIndex(p)->Apply(0);
			m_pMesh->Render();
		}
	}
}

bool CGeometricObject::BuildFX()
{
	VALIDATE(m_pRenderer->BuildFX("color.fx", "ColorTechnique", &m_fxID, &m_techniqueID));

	return true;
}

bool CGeometricObject::CreateFXVarPointers()
{
	m_pTechMatWorld = m_pRenderer->GetFXVariable(m_fxID, "matColorWorld");
	VALIDATE(m_pTechMatWorld != 0);

	m_pTechMatView = m_pRenderer->GetFXVariable(m_fxID, "matColorView");
	VALIDATE(m_pTechMatView != 0);

	m_pTechMatProj = m_pRenderer->GetFXVariable(m_fxID, "matColorProj");
	VALIDATE(m_pTechMatProj != 0);

	return true;
}

bool CGeometricObject::BuildVertexLayout()
{
	VALIDATE(m_pRenderer->BuildVertexLayout(m_pMesh->GetVertexType(), m_techniqueID, &m_vertexLayoutID));

	return true;
}

void CGeometricObject::CalcWorldMatrix()
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