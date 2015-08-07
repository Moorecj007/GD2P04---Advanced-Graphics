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
#include "Defines.h"
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

	// TO DO
	bool BuildFX(std::string _fxFileName, std::string _technique, UINT& _fxID, UINT& _techID);

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

	// TO DO initialize Ids and maps
	UINT nextEffectID;
	std::map<std::string, UINT>* m_pEffectIDs;
	std::map<UINT, ID3D10Effect*>* m_pEffectsbyID;

	UINT nextTechniqueID;
	std::map<UINT, std::map<std::string, UINT>>* m_pTechniqueIDs;
	std::map<UINT, ID3D10EffectTechnique*>* m_pTechniquesbyID;








	
};

#endif // __DX10RENDERER_H__

