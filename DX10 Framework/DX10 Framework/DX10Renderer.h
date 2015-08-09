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

// TO DO - ensure everything is initialised
// Fix the graphics leaks?


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


#include <map>

// Local Includes
#include "Utilities.h"
#include "DX10_Utilities.h"
#include "Vertex.h"

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
	* ClearScreen: Clears the screen to clear color
	* @author: Callan Moore
	* @return: void
	********************/
	void ClearScreen();

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
	* @return: ID3D10EffectVariable*: The Retrieved Effect Variable
	********************/
	ID3D10EffectVariable* GetFXVariable(UINT _fxID, std::string _techVar);

	/***********************
	* BuildVertexLayout: Detect the Vertex Description Needed
	* @author: Callan Moore
	* @Parameter: _vertType: Vertex structure to base layout on
	* @Parameter: _techID: Technique ID to base the layout on
	* @Parameter: _vertexLayoutID: Storage variable to hold the ID of the created Vertex Layout
	* @return: bool: Successful or not
	********************/
	bool BuildVertexLayout(eVertexType _vertType, UINT _techID, UINT* _vertexLayoutID);

	/***********************
	* CreateVertexLayout: Create the Vertex Layout for an Object
	* @author: Callan Moore
	* @parameter: _vertexDesc: Description of the Vertices's
	* @parameter: _elementNum: Number of elements in the Vertex Description
	* @parameter: _techID: Technique ID to base the layout on
	* @Parameter: _vertexLayoutID: Storage variable to hold the ID of the created Vertex Layout
	* @return: bool
	********************/
	bool CreateVertexLayout(D3D10_INPUT_ELEMENT_DESC _vertexDesc[], UINT _elementNum, UINT _techID, UINT* _vertexLayoutID);

	/***********************
	* CreateVertexBuffer: Create an Vertex Buffer with the given data
	* @author: Callan Moore
	* @parameter: _pVertices: Array of Vertex Points
	* @parameter: _vertCount: Number of Vertices
	* @parameter: _vertexBufferID: Storage value to hold the ID of the created Vertex buffer
	* @return: bool: Successful or not
	********************/
	template<typename T>
	bool CreateVertexBuffer(typename T* _pVertices, UINT _vertCount, UINT* _vertexBufferID)
	{
		D3D10_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
		vertexBufferDesc.ByteWidth = sizeof(T) * _vertCount;
		vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D10_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = _pVertices;

		ID3D10Buffer* vertexBuffer;
		if (FAILED(m_pDX10Device->CreateBuffer(&vertexBufferDesc, &subResourceData, &vertexBuffer)))
		{
			// Release a potentially created buffer
			ReleaseCOM(vertexBuffer);
			return false;
		}

		*_vertexBufferID = ++nextVertexBufferID;
		std::pair<UINT, ID3D10Buffer*> vbPair(nextVertexBufferID, vertexBuffer);
		(m_vertexBuffers.insert(vbPair).second);

		return true;
	}

	/***********************
	* CreateIndexBuffer: Create an Index Buffer with the given data
	* @author: Callan Moore
	* @parameter: _indices: Array if Indices points
	* @parameter: _indexCount: Number of Indices
	* @parameter: _indexBufferID: Storage value to hold the ID of the created Index buffer
	* @return: bool: Successful or not
	********************/
	bool CreateIndexBuffer(DWORD* _indices, UINT _indexCount, UINT* _indexBufferID);

	/***********************
	* RenderObject: Renders an Object to the screen
	* @author: Callan Moore
	* @parameter: _vertexID: The ID of the Vertex buffer stored on the Renderer
	* @parameter: _indexID: The ID of the Index buffer stored on the Renderer
	* @parameter: _indexCount: The number of indices
	* @parameter: _stride: Stride of the Vertex Buffer
	* @return: bool: Successful or not
	********************/
	bool RenderObject(UINT _vertexID, UINT  _indexID, UINT _indexCount, UINT _stride);

	/***********************
	* StartRender: Clears the Back buffer ready for new frame
	* @author: Callan Moore
	* @return: void
	********************/
	void StartRender();

	/***********************
	* EndRender: Presents the Back buffer
	* @author: Callan Moore
	* @return: void
	********************/
	void EndRender();

	/***********************
	* RestoreDefaultDrawStates: Restore the default states for drawing to ensure correct states
	* @author: Callan Moore
	* @return: void
	********************/
	void RestoreDefaultDrawStates();

	/***********************
	* SetInputLayout: Set the Vertex Layout as the Input Layout on the Renderer
	* @author: Callan Moore
	* @parameter: _vertexLayoutID: Vertex Layout ID
	* @return: bool: Successful or not
	********************/
	bool SetInputLayout(UINT _vertexLayoutID);

	/***********************
	* GetTechnique: Retrieve the Technique for the given ID
	* @author: Callan Moore
	* @parameter: _techID: ID of the Technique
	* @return: ID3D10EffectTechnique*: DX10 Technique
	********************/
	ID3D10EffectTechnique* GetTechnique(UINT _techID);


	/***********************
	* CalcViewMatrix: Calculate the View Matrix for use in Renderering
	* @author: Callan Moore
	* @return: void
	********************/
	void CalcViewMatrix();
	
	/***********************
	* CalcProjMatrix: Calculate the Projection Matrix for use in Renderering
	* @author: Callan Moore
	* @return: void
	********************/
	void CalcProjMatrix();
	
	/***********************
	* GetViewMatrix: Retrieve the View Matrix
	* @author: Callan Moore
	* @return: D3DXMATRIX*: The View Matrix
	********************/
	D3DXMATRIX* GetViewMatrix();
	
	/***********************
	* GetProjMatrix: Retrieve the Projection Matrix
	* @author: Callan Moore
	* @return: D3DXMATRIX*: The Projection Matrix
	********************/
	D3DXMATRIX* GetProjMatrix();

private:
	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;
	bool m_fullScreen;

	// Matrices for Rendering
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

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
	std::map<UINT, ID3D10EffectTechnique*> m_techniquesByID;

	UINT nextInputLayoutID;
	std::map<UINT, ID3D10InputLayout*> m_inputLayouts;

	UINT nextVertexBufferID;
	std::map<UINT, ID3D10Buffer*> m_vertexBuffers;

	UINT nextIndexBufferID;
	std::map<UINT, ID3D10Buffer*> m_indexBuffers;
};

#endif // __DX10RENDERER_H__

