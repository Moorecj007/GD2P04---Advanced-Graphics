/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Obj_LitTex.h
* Description : 3D Lit Texture Object for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DX10_Obj_LitTex.h"

DX10_Obj_LitTex::DX10_Obj_LitTex()
{
	DX10_Obj_Generic::BaseInitialise();
}

DX10_Obj_LitTex::~DX10_Obj_LitTex()
{
}

void DX10_Obj_LitTex::Draw()
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
			m_pTechObjColor->SetFloatVector((float*)m_color);
			m_pTechMatWorld->SetMatrix((float*)m_matWorld);
			m_pTechMatView->SetMatrix((float*)*m_pRenderer->GetViewMatrix());
			m_pTechMatProj->SetMatrix((float*)*m_pRenderer->GetProjMatrix());

			pTech->GetPassByIndex(p)->Apply(0);
			m_pMesh->Render();
		}
	}
}

bool DX10_Obj_LitTex::BuildFX()
{
	VALIDATE(m_pRenderer->BuildFX("color.fx", "ColorTechnique", &m_fxID, &m_techniqueID));

	return true;
}

bool DX10_Obj_LitTex::CreateFXVarPointers()
{
	m_pTechMatWorld = m_pRenderer->GetFXVariable(m_fxID, "matColorWorld")->AsMatrix();
	VALIDATE(m_pTechMatWorld != 0);

	m_pTechMatView = m_pRenderer->GetFXVariable(m_fxID, "matColorView")->AsMatrix();
	VALIDATE(m_pTechMatView != 0);

	m_pTechMatProj = m_pRenderer->GetFXVariable(m_fxID, "matColorProj")->AsMatrix();
	VALIDATE(m_pTechMatProj != 0);

	m_pTechObjColor = m_pRenderer->GetFXVariable(m_fxID, "objColor")->AsVector();
	VALIDATE(m_pTechObjColor != 0);

	return true;
}
