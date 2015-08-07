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
#include <d3dx10.h>

// Local Includes
#include "Defines.h"


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
	* @Parameter: _iclientWidth: Width of the screen
	* @Parameter: _iclientHeight: Height of the screen
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

	void onResize();

	/***********************
	* RenderFrame: Render a single frame
	* @author: Callan Moore
	* @return: void
	********************/
	void RenderFrame();

private:
	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;

	// DX10 Variables
	ID3D10Device*    m_dx10Device;
	IDXGISwapChain*  m_dx10SwapChain;
	ID3D10RenderTargetView* m_renderTargetView;

	D3D10_DRIVER_TYPE m_dx10DriverType;
	D3DXCOLOR m_clearColor;
	
};

#endif // __DX10RENDERER_H__

