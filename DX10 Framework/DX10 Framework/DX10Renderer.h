/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10Renderer.h
* Description : Holds the DirectX10 Device and Renders all Objects created by the DirectX10 device
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10RENDERER_H__
#define __DX10RENDERER_H__

// Linker Includes
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10d.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")

// Library Includes
#include <d3d10.h>
#include <dxerr.h>
#include <map>

// Local Includes
#include "Utilities.h"
#include "Vertex.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef VALIDATEHR
	#define VALIDATEHR(x)                                      \
	{														   \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
			return false;									   \
		}                                                      \
	}
#endif
#else
	#ifndef VALIDATEHR
	#define VALIDATEHR(x) (x)
	#endif
#endif 


class CDX10Renderer
{
public:
	
	/***********************
	* CDX10Renderer: Default Constructor for DX10 Renderer class
	* @author: Callan Moore
	********************/
	CDX10Renderer();

	/***********************
	* Initialise: Initialise the DX10 Renderer
	* @author: Callan Moore
	* @Parameter: _clientWidth: Width of the client window
	* @Parameter: _clientHeight: Height of the client window
	* @Parameter: _hWND: Handle to the Application window
	* @return: bool: Successful or not
	********************/
	bool Initialise(int _clientWidth, int _clientHeight, HWND _hWND);

	/***********************
	* ~CDX10Renderer: Default Destructor for DX10 Renderer class
	* @author: Callan Moore
	********************/
	~CDX10Renderer();

	/***********************
	* ShutDown: Shuts down and releases all memory created by DX10 Renderer
	* @author: Callan Moore
	* @return: void
	********************/
	void ShutDown();

	/***********************
	* InitialiseDeviceAndSwapChain: Initialise the DX10 Device and Swap Chain
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool InitialiseDeviceAndSwapChain();

	/***********************
	* onResize: Recreate Depth and Render Views when resizing the application
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool onResize();

	/***********************
	* RenderFrame: Render a single frame
	* @author: Callan Moore
	* @return: void
	********************/
	void RenderFrame();

	/***********************
	* ToggleFullscreen: Toggle Full screen on and off
	* @author: Callan Moore
	* @return: void
	********************/
	void ToggleFullscreen();

	/***********************
	* BuildFX: Build a FX file and Technique and store on the Renderer
	* @author: Callan Moore
	* @Parameter: _fxFileName: Name of the Effects file to retrieve
	* @Parameter: _technique: Name of the Technique to Retrieve from the FX file
	* @Parameter: _fxID: Storage value to hold the created or found ID of the FX file
	* @Parameter: _techID: Storage value to hold the created or found ID of the Technique
	* @return: bool: Successful or not
	********************/
	bool BuildFX(std::string _fxFileName, std::string _technique, UINT* _fxID, UINT* _techID);

	/***********************
	* GetFXVariable: Retrieve a FX Variable
	* @author: Callan Moore
	* @Parameter: _fxID: ID of the FX file to access
	* @Parameter: _techVar: Name of the variable to retrieve
	* @Parameter: _fxVar: Storage variable to hold the retrieved variable
	* @return: bool: Successful or not
	********************/
	bool GetFXVariable(UINT _fxID, std::string _techVar, ID3D10EffectVariable* _fxVar);

	/***********************
	* BuildVertexLayout: Build a Vertex Layout 
	* @author: Callan Moore
	* @Parameter: _vertStruct: Vertex structure to base layout on
	* @Parameter: _techID: Technique ID to base the layout on
	* @Parameter: _vertexLayoutID: Storage variable to hold the ID of the created Vertex Layout
	* @return: bool: Successful or not
	********************/
	template <typename T>
	bool BuildVertexLayout(T _vertStruct, UINT _techID, UINT* _vertexLayoutID);
	//{
	//	D3D10_INPUT_ELEMENT_DESC _vertStruct[]
	//
	//	switch (typeid(vertStruct))
	//	{
	//		case TVertexBasic :
	//		{
	//			vertexDesc[] =
	//			{ 
	//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	//			};
	//		}
	//		break;
	//		case TVertexColor :
	//		{
	//			vertexDesc[] =
	//			{
	//				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	//				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	//			};
	//		}
	//		break;
	//		default:
	//		{
	//			return false;
	//		}
	//		break;
	//	}	// End Switch
	//
	//	// Find the Technique using the ID
	//	ID3D10EffectTechnique* pTech = m_techniquesbyID.find(_techID);
	//	ID3D10InputLayout* pVertexLayout;
	//
	//	// Create the input layout
	//	D3D10_PASS_DESC passDesc;
	//	pTech->GetPassByIndex(0)->GetDesc(&passDesc);
	//	VALIDATEHR(	m_pDX10Device->CreateInputLayout(_vertStruct, 2, passDesc.pIAInputSignature,
	//				passDesc.IAInputSignatureSize, &pVertexLayout));
	//
	//	UINT inputLayerID = ++nextInputLayoutID;
	//	std::pair<UINT, ID3D10InputLayout*> inputLayerPair(inputLayerID, pVertexLayout);
	//	VALIDATE(m_inputLayout.insert(inputLayerPair));
	//
	//	return true;
	//}

	// TO DO - Create a damn cube!!!!!

private:
	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;
	bool m_fullScreen;

	// DX10 Variables
	ID3D10Device*    m_pDX10Device;
	IDXGISwapChain*  m_pDX10SwapChain;
	ID3D10RenderTargetView* m_pRenderTargetView;

	D3D10_DRIVER_TYPE m_dx10DriverType;
	D3DXCOLOR m_clearColor;

	UINT nextEffectID;
	std::map<std::string, UINT> m_effectIDs;
	std::map<UINT, ID3D10Effect*> m_effectsbyID;

	UINT nextTechniqueID;
	std::map<UINT, std::map<std::string, UINT>> m_techniqueIDs;
	std::map<UINT, ID3D10EffectTechnique*> m_techniquesbyID;

	UINT nextInputLayoutID;
	std::map<UINT, ID3D10InputLayout*> m_inputLayout;


	
};

#endif // __DX10RENDERER_H__

