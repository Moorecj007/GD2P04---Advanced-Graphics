/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Shader_LitTex.cpp
* Description : Shader Instructions for a the LitTexture shader
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_SHADER_LITTEX_H__
#define __DX10_SHADER_LITTEX_H__

// Local Includes
#include "../../../Utility/Utilities.h"
#include "../DX10_Utilities.h"
#include "../DX10_Renderer.h"
#include "../DX10_Shader_Structures.h"

class DX10_Shader_LitTex
{
public:

	/***********************
	* DX10_Shader_LitTex: Default Constructor for Lit Texture Shader class
	* @author: Callan Moore
	********************/
	DX10_Shader_LitTex()
	{
	}

	/***********************
	* ~DX10_Shader_LitTex: Default Destructor for Lit Texture Shader class
	* @author: Callan Moore
	********************/
	~DX10_Shader_LitTex()
	{
	}

	/***********************
	* Initialise: Initialise the shader for use
	* @author: Callan Moore
	* @parameter: _pDX10_Renderer: DX10 Renderer for this application
	* @return: bool: Successful or not
	********************/
	bool Initialise(DX10_Renderer* _pDX10_Renderer)
	{
		m_pDX10_Renderer = _pDX10_Renderer;

		VALIDATE(BuildFX());
		VALIDATE(CreateFXVarPointers());
		VALIDATE(CreateVertexLayout());

		VALIDATE(m_pDX10_Renderer->CreateTexture("defaultSpecular.dds", &m_specularID));

		return true;
	}
	
	/***********************
	* SetUpPerFrame: Setup the shader file with the variables used for the whole frame
	* @author: Callan Moore
	* @return: void
	********************/
	void SetUpPerFrame()
	{
		m_pLight->SetRawValue(m_pDX10_Renderer->GetActiveLight(), 0, sizeof(Light));
		m_pEyePos->SetRawValue(m_pDX10_Renderer->GetEyePos(), 0, sizeof(D3DXVECTOR3));
		m_pMatView->SetMatrix((float*)m_pDX10_Renderer->GetViewMatrix());
		m_pMatProj->SetMatrix((float*)m_pDX10_Renderer->GetProjMatrix());
	}
	
	/***********************
	* Render: Ready the shader technique with object specific details and setting the objects mesh to render
	* @author: Callan Moore
	* @parameter: _litTex: Structure containing all details for a litTex object
	* @return: void
	********************/
	void Render(TLitTex _litTex)
	{
		// Reset draw states in case they're different
		m_pDX10_Renderer->RestoreDefaultDrawStates();

		// Set the Renderer Input layout and primitive topology to be the correct ones for this shader
		m_pDX10_Renderer->SetInputLayout(m_vertexLayoutID);
		m_pDX10_Renderer->SetPrimitiveTopology(_litTex.pMesh->GetPrimTopology());

		// Retrieve the Technique
		ID3D10EffectTechnique* pTech = m_pDX10_Renderer->GetTechnique(m_techniqueID);

		// Don't transform texture coordinates
		D3DXMATRIX matTex;
		D3DXMatrixIdentity(&matTex);
<<<<<<< HEAD
		D3DXMatrixTranslation(&matTex, 0.5, 0, 0);
=======

		D3DXMATRIX matTranslation;
		D3DXMatrixIdentity(&matTranslation);
		D3DXMatrixTranslation(&matTranslation, (float)_litTex.textureID / 120.0f, 0, 0);

		matTex = matTex * matTranslation;
>>>>>>> origin/master

		if (pTech != NULL)
		{
			D3D10_TECHNIQUE_DESC techDesc;
			pTech->GetDesc(&techDesc);
			for (UINT p = 0; p < techDesc.Passes; ++p)
			{
				D3DXMATRIX matWorld = *_litTex.pMatWorld;

				m_pMatWorld->SetMatrix((float*)&matWorld);
				m_pMatTex->SetMatrix((float*)&matTex);
				m_pMapDiffuse->SetResource(m_pDX10_Renderer->GetTexture(_litTex.textureID));
				m_pMapSpecular->SetResource(m_pDX10_Renderer->GetTexture(m_specularID));

				pTech->GetPassByIndex(p)->Apply(0);
				_litTex.pMesh->Render();
			}
		}
	}

private:
	
	/***********************
	* BuildFX: Build the FX file for the Shader
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool BuildFX()
	{
		VALIDATE(m_pDX10_Renderer->BuildFX("litTex.fx", "LitTextureTech", &m_fxID, &m_techniqueID));

		return true;
	}

	/***********************
	* CreateFXVarPointers: Create the pointers to the FX memory on the graphics card
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool CreateFXVarPointers()
	{
		// Per Frame
		m_pLight = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_light");
		m_pEyePos = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_eyePosW");

		m_pMatView = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_matView")->AsMatrix();
		m_pMatProj = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_matProj")->AsMatrix();

		// Per Object
		m_pMatWorld = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_matWorld")->AsMatrix();
		m_pMatTex = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_matTex")->AsMatrix();

		// Globals
		m_pMapDiffuse = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_mapDiffuse")->AsShaderResource();
		m_pMapSpecular = m_pDX10_Renderer->GetFXVariable(m_fxID, "g_mapSpec")->AsShaderResource();

		VALIDATE(m_pLight != 0);
		VALIDATE(m_pEyePos != 0);
		VALIDATE(m_pMatView != 0);
		VALIDATE(m_pMatProj != 0);
		VALIDATE(m_pMatWorld != 0);
		VALIDATE(m_pMatTex != 0);
		VALIDATE(m_pMapDiffuse != 0);
		VALIDATE(m_pMapSpecular != 0);

		return true;
	}

	/***********************
	* CreateVertexLayout: Create the vertex layout for this shader
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool CreateVertexLayout()
	{
		// Vertex Desc for a basic vertex with Normals and UV coordinates
		D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT elementNum = 3;
		m_pDX10_Renderer->CreateVertexLayout(vertexDesc, elementNum, m_techniqueID, &m_vertexLayoutID);
	
		return true;
	}

private:

	UINT m_fxID;
	UINT m_techniqueID;
	UINT m_vertexLayoutID;
	UINT m_specularID;

	DX10_Renderer*						m_pDX10_Renderer;

	ID3D10EffectVariable*				m_pLight;
	ID3D10EffectVariable*				m_pEyePos;
	ID3D10EffectMatrixVariable*			m_pMatView;
	ID3D10EffectMatrixVariable*			m_pMatProj;

	ID3D10EffectMatrixVariable*			m_pMatWorld;
	ID3D10EffectMatrixVariable*			m_pMatTex;

	ID3D10EffectShaderResourceVariable* m_pMapDiffuse;
	ID3D10EffectShaderResourceVariable* m_pMapSpecular;
};

#endif	// __DX10_SHADER_LITTEX_H__