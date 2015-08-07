/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10Renderer.cpp
* Description : Holds the DirectX10 Device and Renders all Objects created by the DirectX10 device
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DX10Renderer.h"

CDX10Renderer::CDX10Renderer()
{
	m_dx10Device = 0;
	m_dx10SwapChain = 0;
	m_renderTargetView = 0;
}

bool CDX10Renderer::Initialise(int _clientWidth, int _clientHeight, HWND _hWND)
{
	// Save Window Variables
	m_hWnd = _hWND;
	m_clientWidth = _clientWidth;
	m_clientHeight = _clientHeight;

	VALIDATE(InitialiseDeviceAndSwapChain());

	m_clearColor = D3DXCOLOR(255.0f, 255.0f, 0.0f, 1.0f);
	return true;
}

CDX10Renderer::~CDX10Renderer()
{
}

void CDX10Renderer::ShutDown()
{
	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_dx10SwapChain);
	ReleaseCOM(m_dx10Device);
}

bool CDX10Renderer::InitialiseDeviceAndSwapChain()
{
	// State the Driver to be of type HAL
	m_dx10DriverType = D3D10_DRIVER_TYPE_HARDWARE;

	// Fill out the DXGI Swap Chain Description structure
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_clientWidth;
	sd.BufferDesc.Height = m_clientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// No multi sampling per pixel ( 1 sample only) and low quality
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = m_hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// Add Debug Info to the flags when run in Debug mode
	UINT createDeviceFlags = 0;
	#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
	#endif
	
	// Create the Device and Swap Chain
	if( FAILED(	D3D10CreateDeviceAndSwapChain(
					0,                 //default adapter
					m_dx10DriverType,
					0,                 // no software device
					createDeviceFlags,
					D3D10_SDK_VERSION,
					&sd,
					&m_dx10SwapChain,
					&m_dx10Device)))
	{
		// Creation failed
		return false;
	}
	
	// Invoke functionality that deals with changing size of the window
	onResize();

	return true;
}

void CDX10Renderer::onResize()
{
	// Release the old render target view before creating again
	ReleaseCOM(m_renderTargetView);
	
	// Resize the buffers of the Swap Chain and create the new render target view
	m_dx10SwapChain->ResizeBuffers(1, m_clientWidth, m_clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	// Create a temporary Back buffer
	ID3D10Texture2D* pBackBuffer;

	// Retrieve the Back Buffer of the Swap Chain and create a Render Target View using the Back Buffer
	m_dx10SwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	m_dx10Device->CreateRenderTargetView(pBackBuffer, 0, &m_renderTargetView);

	// Release the memory from the temporary Back Buffer
	ReleaseCOM(pBackBuffer);
	
	// Bind the Render Target View to the output-merger stage of the pipeline
	m_dx10Device->OMSetRenderTargets(1, &m_renderTargetView, NULL);
	
	// Set the View Port for the Device
	D3D10_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = m_clientWidth;
	viewPort.Height = m_clientHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	
	// Binds the View port to the Rasterizer stage of the pipeline
	m_dx10Device->RSSetViewports(1, &viewPort);
}

void CDX10Renderer::RenderFrame()
{
	// Color Fill the entire Render Target View(Back Buffer) with the Renderers clear color
	m_dx10Device->ClearRenderTargetView(m_renderTargetView, m_clearColor);
	
	// Present the Back Buffer with no synchronization
	m_dx10SwapChain->Present(0, 0);
}