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
	m_pDX10Device = 0;
	m_pDX10SwapChain = 0;
	m_pRenderTargetView = 0;
}

bool CDX10Renderer::Initialise(int _clientWidth, int _clientHeight, HWND _hWND)
{
	// Save Window Variables
	m_hWnd = _hWND;
	m_clientWidth = _clientWidth;
	m_clientHeight = _clientHeight;

	VALIDATE(InitialiseDeviceAndSwapChain());

	m_clearColor = D3DXCOLOR(255.0f, 255.0f, 0.0f, 1.0f);

	//Initialise the ID Keys for the Maps
	nextEffectID = 0;
	nextTechniqueID = 0;
	nextInputLayoutID = 0;


	return true;
}

CDX10Renderer::~CDX10Renderer()
{
}

void CDX10Renderer::ShutDown()
{
	ReleaseCOM(m_pRenderTargetView);
	ReleaseCOM(m_pDX10SwapChain);
	ReleaseCOM(m_pDX10Device);
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
	VALIDATEHR(	D3D10CreateDeviceAndSwapChain(
				0,                 //default adapter
				m_dx10DriverType,
				0,                 // no software device
				createDeviceFlags,
				D3D10_SDK_VERSION,
				&sd,
				&m_pDX10SwapChain,
				&m_pDX10Device));
	
	
	// Invoke functionality that deals with changing size of the window
	VALIDATE(onResize());

	return true;
}

bool CDX10Renderer::onResize()
{
	// Release the old render target view before creating again
	ReleaseCOM(m_pRenderTargetView);
	
	// Resize the buffers of the Swap Chain and create the new render target view
	VALIDATEHR(m_pDX10SwapChain->ResizeBuffers(1, m_clientWidth, m_clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

	// Create a temporary Back buffer
	ID3D10Texture2D* pBackBuffer;

	// Retrieve the Back Buffer of the Swap Chain and create a Render Target View using the Back Buffer
	VALIDATEHR(m_pDX10SwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pBackBuffer)));
	VALIDATEHR(m_pDX10Device->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView));

	// Release the memory from the temporary Back Buffer
	ReleaseCOM(pBackBuffer);
	
	// Bind the Render Target View to the output-merger stage of the pipeline
	m_pDX10Device->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	
	// Set the View Port for the Device
	D3D10_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = m_clientWidth;
	viewPort.Height = m_clientHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	
	// Binds the View port to the Rasterizer stage of the pipeline
	m_pDX10Device->RSSetViewports(1, &viewPort);

	return true;
}

void CDX10Renderer::RenderFrame()
{
	// Color Fill the entire Render Target View(Back Buffer) with the Renderers clear color
	m_pDX10Device->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
	
	// Present the Back Buffer with no synchronization
	m_pDX10SwapChain->Present(0, 0);
}

void CDX10Renderer::ToggleFullscreen()
{
	m_fullScreen = !m_fullScreen;
	m_pDX10SwapChain->SetFullscreenState(m_fullScreen, NULL);
}

bool CDX10Renderer::BuildFX(std::string _fxFileName, std::string _technique, UINT* _fxID, UINT* _techID)
{	
	ID3D10Effect* pFX = 0;
	UINT fxID;
	UINT techID;

	// Adding the Effect File to the Map
	std::map<std::string, UINT>::iterator fxCheck;
	fxCheck = m_effectIDs.find(_fxFileName);

	if (fxCheck != m_effectIDs.end())
	{
		fxID = fxCheck->second;
		pFX = m_effectsbyID.find(fxID)->second;
	}
	else
	{
		DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
		#if defined( DEBUG ) || defined( _DEBUG )
			shaderFlags |= D3D10_SHADER_DEBUG;
			shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
		#endif
		
		ID3D10Blob* compilationErrors;
		VALIDATEHR(	D3DX10CreateEffectFromFileA(_fxFileName.c_str(), 0, 0,
					"fx_4_0", shaderFlags, 0, m_pDX10Device, 0, 0, &pFX, &compilationErrors, 0));
		ReleaseCOM(compilationErrors);
		
		fxID = ++nextEffectID;
		std::pair<std::string, UINT> fxPair(_fxFileName, fxID);
		std::pair<UINT, ID3D10Effect*> fxPairByID(fxID, pFX);

		VALIDATE(m_effectIDs.insert(fxPair).second);
		VALIDATE(m_effectsbyID.insert(fxPairByID).second);
	}


	// Adding the Technique to the Map
	std::map<UINT, std::map<std::string, UINT>>::iterator fxIDCheck;
	fxIDCheck = m_techniqueIDs.find(fxID);

	if (fxIDCheck != m_techniqueIDs.end())
	{
		std::map<std::string, UINT>::iterator techIDCheck;
		techIDCheck = fxIDCheck->second.find(_technique);

		if (techIDCheck != fxIDCheck->second.end())
		{
			techID = fxCheck->second;
		}
		else
		{
			ID3D10EffectTechnique* pTech = pFX->GetTechniqueByName(_technique.c_str());

			techID = ++nextTechniqueID;
			std::pair<std::string, UINT> techPair(_technique, techID);
			std::pair<UINT, ID3D10EffectTechnique*> techPairByID(techID, pTech);

			VALIDATE((&fxIDCheck->second)->insert(techPair).second);
			VALIDATE(m_techniquesbyID.insert(techPairByID).second);
		}
	}
	else
	{
		ID3D10EffectTechnique* pTech = pFX->GetTechniqueByName(_technique.c_str());

		techID = ++nextTechniqueID;
		std::map<std::string, UINT> innerTechMap;
		std::pair<std::string, UINT> innerTechPair(_technique, techID);
		VALIDATE(innerTechMap.insert(innerTechPair).second);

		std::pair<UINT, std::map<std::string, UINT>> outerTechMap(fxID, innerTechMap);
		VALIDATE(m_techniqueIDs.insert(outerTechMap).second);

		std::pair<UINT, ID3D10EffectTechnique*> techByIDPair(techID, pTech);
		VALIDATE(m_techniquesbyID.insert(techByIDPair).second);
	}

	// Save the FX and Technique IDs in the memory passed by the Object.
	*_fxID = fxID;
	*_techID = techID;
	return true;
}

bool CDX10Renderer::GetFXVariable(UINT _fxID, std::string _techVar, ID3D10EffectVariable* _fxVar)
{
	// Retrieve the FX pointer
	ID3D10Effect* pFX = m_effectsbyID.find(_fxID)->second;
	_fxVar = pFX->GetVariableByName(_techVar.c_str());

	return ((_fxVar == NULL) ? false : true);
}

template <typename T>
bool BuildVertexLayout(T _vertStruct, UINT _techID, UINT* _vertexLayoutID)
{
	D3D10_INPUT_ELEMENT_DESC _vertStruct[]

		switch (typeid(vertStruct))
	{
		case TVertexBasic:
		{
			vertexDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
			};
		}
		break;
		case TVertexColor:
		{
			vertexDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
			};
		}
		break;
		default:
		{
			return false;
		}
		break;
	}	// End Switch

	// Find the Technique using the ID
	ID3D10EffectTechnique* pTech = m_techniquesbyID.find(_techID);
	ID3D10InputLayout* pVertexLayout;

	// Create the input layout
	D3D10_PASS_DESC passDesc;
	pTech->GetPassByIndex(0)->GetDesc(&passDesc);
	VALIDATEHR(m_pDX10Device->CreateInputLayout(_vertStruct, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &pVertexLayout));

	UINT inputLayerID = ++nextInputLayoutID;
	std::pair<UINT, ID3D10InputLayout*> inputLayerPair(inputLayerID, pVertexLayout);
	VALIDATE(m_inputLayout.insert(inputLayerPair));

	*_vertexLayoutID = inputLayerID;
	return true;
}