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

DX10_Obj_LitTex::DX10_Obj_LitTex(DX10_Shader_LitTex* _pShader, UINT _textureID)
{
	DX10_Obj_Generic::BaseInitialise();

	m_pShader = _pShader;
	m_textureID = _textureID;
}

DX10_Obj_LitTex::~DX10_Obj_LitTex()
{
}

void DX10_Obj_LitTex::Render()
{
	TLitTex litTex;
	litTex.pMesh = m_pMesh;
	litTex.pMatWorld = &m_matWorld;
	litTex.textureID = m_textureID;

	m_pShader->Render(litTex);
}
