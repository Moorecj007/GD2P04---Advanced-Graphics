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
	m_pTechMatWorld = 0;
	m_pTechMatView = 0;
	m_pTechMatProj = 0;
}

CCube::~CCube()
{
	
}

bool CCube::Initialise(CDX10Renderer* _pRenderer)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	// TO DO - Put in Mesh class
	float scale = 1.0f;
	float vertSize = 1.0f * scale / 2;
	// Create vertex buffer
	TVertexColor vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), BLACK },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), BLACK },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), BLACK },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), BLACK },
	
		// Left
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), RED },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), RED },
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), RED },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), RED },
	
		// Right
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), GREEN },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), GREEN },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), GREEN },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), GREEN },
	
		// Back
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), BLUE },
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), BLUE },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), BLUE },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), BLUE },
	
		// Top
		{ D3DXVECTOR3(-vertSize, vertSize, vertSize), MAGENTA },
		{ D3DXVECTOR3(vertSize, vertSize, vertSize), MAGENTA },
		{ D3DXVECTOR3(vertSize, vertSize, -vertSize), MAGENTA },
		{ D3DXVECTOR3(-vertSize, vertSize, -vertSize), MAGENTA },
	
		// Bottom
		{ D3DXVECTOR3(-vertSize, -vertSize, -vertSize), WHITE },
		{ D3DXVECTOR3(vertSize, -vertSize, -vertSize), WHITE },
		{ D3DXVECTOR3(vertSize, -vertSize, vertSize), WHITE },
		{ D3DXVECTOR3(-vertSize, -vertSize, vertSize), WHITE }
	};
	m_stride = sizeof(*vertices);
	m_vertexCount = (sizeof(vertices) / m_stride);
	
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
	m_indexCount = (sizeof(indices) / sizeof(*indices));
	
	m_pRenderer->CreateStaticBuffer(vertices, indices, m_vertexCount, m_indexCount, m_stride, &m_bufferID);

	// Set up the Cube for with its shaders and draw instructions
	BuildFX();
	CreateFXVarPointers();
	BuildVertexLayout();

	return true;
}

void CCube::Process(float _dt)
{

}

void CCube::Draw()
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
			m_pRenderer->RenderObject(m_bufferID);
		}
	}
}

bool CCube::BuildFX()
{
	VALIDATE(m_pRenderer->BuildFX("color.fx", "ColorTechnique", &m_fxID, &m_techniqueID));

	return true;
}

bool CCube::CreateFXVarPointers()
{
	m_pTechMatWorld = m_pRenderer->GetFXVariable(m_fxID, "matColorWorld");
	VALIDATE(m_pTechMatWorld != 0);

	m_pTechMatView = m_pRenderer->GetFXVariable(m_fxID, "matColorView");
	VALIDATE(m_pTechMatView != 0);

	m_pTechMatProj = m_pRenderer->GetFXVariable(m_fxID, "matColorProj");
	VALIDATE(m_pTechMatProj != 0);

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