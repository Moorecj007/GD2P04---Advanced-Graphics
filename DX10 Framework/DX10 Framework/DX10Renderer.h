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
#include <map>
#include <typeinfo> 
#include <time.h>
#include <DXGIDebug.h>

// Local Includes
#include "Utilities.h"
#include "DX10_Utilities.h"
#include "Vertex.h"
#include "StaticBuffer.h"

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
	* ToggleFillMode: Toggle fill mode between solid and wireframe
	* @author: Callan Moore
	* @return: void
	********************/
	void ToggleFillMode();

	/***********************
	* BuildFX: Build a FX file and Technique and store on the Renderer
	* @author: Callan Moore
	* @Parameter: _fxFileName: Name of the Effects file to retrieve
	* @Parameter: _technique: Name of the Technique to Retrieve from the FX file
	* @Parameter: _fxID: Storage value to hold the created or found ID of the FX file
	* @Parameter: _techID: Storage value to hold the created or found ID of the Technique
	* @return: bool: Successful or not
	********************/
	bool BuildFX(std::string _fxFileName, std::string _technique, UINT* _pFXID, UINT* _pTechID);

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
	* @Parameter: _pVertexLayoutID: Storage variable to hold the ID of the created Vertex Layout
	* @return: bool: Successful or not
	********************/
	bool BuildVertexLayout(eVertexType _vertType, UINT _techID, UINT* _pVertexLayoutID);

	/***********************
	* CreateVertexLayout: Create the Vertex Layout for an Object
	* @author: Callan Moore
	* @parameter: _vertexDesc: Description of the Vertices's
	* @parameter: _elementCount: Number of elements in the Vertex Description
	* @parameter: _techID: Technique ID to base the layout on
	* @Parameter: _vertexLayoutID: Storage variable to hold the ID of the created Vertex Layout
	* @return: bool: Successful or not
	********************/
	bool CreateVertexLayout(D3D10_INPUT_ELEMENT_DESC _vertexDesc[], UINT _elementCount, UINT _techID, UINT* _pVertexLayoutID);

	/***********************
	* CreateStaticBuffer: Creates a static buffer that holds all information for Vertex and Index Buffers for an Mesh
	* @author: Callan Moore
	* @parameter: _pVertices: The array of Vertices
	* @parameter: _pIndices: The array of Indices
	* @parameter: _vertCount: Number of Vertices
	* @parameter: _indexCount: Number of Indices
	* @parameter: _stride: Stride size for each Vertex
	* @parameter: _pBufferID: Storage variable to hold the ID of the created static buffer
	* @return: bool: Successful or not
	********************/
	template<typename TIndices, typename TVertices>
	bool CreateStaticBuffer(typename TVertices* _pVertices, typename TIndices* _pIndices,
		UINT _vertCount, UINT _indexCount, UINT _stride, UINT* _pBufferID)
	{
		*_pBufferID = ++m_nextBufferID;

		CStaticBuffer* staticBuff = new CStaticBuffer(m_pDX10Device);
		if (staticBuff->Initialise(_pVertices, _pIndices, _vertCount, _indexCount, _stride, _pBufferID))
		{
			std::pair<UINT, CStaticBuffer*> bufferPair(m_nextBufferID, staticBuff);
			VALIDATE(m_staticBuffers.insert(bufferPair).second);

			return true;
		}
		else
		{
			// Delete the failed static buffer memory
			_pBufferID = 0;
			delete staticBuff;
			staticBuff = 0;
			return false;
		}
	}

	/***********************
	* RenderObject: Renders an Object to the screen
	* @author: Callan Moore
	* @parameter: _vertexID: The ID of the static buffer stored on the Renderer
	* @return: bool: Successful or not
	********************/
	bool RenderMesh(UINT _bufferID);

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
	* SetPrimitiveTopology: Sets the primitive topology for a Mesh before drawing
	* @author: Callan Moore
	* @parameter: _primitiveType: The Primitive type/topology for the Mesh
	* @return: void
	********************/
	void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _primitiveType);

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
	* SetViewMatrix: Set the View Matrix for use in Renderering
	* @author: Callan Moore
	* @parameter: _view: The new View matrix
	* @return: void
	********************/
	void SetViewMatrix(D3DXMATRIX _view);
	
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
	D3D10_RASTERIZER_DESC m_rasterizerDesc;
	ID3D10RasterizerState* m_pRasterizerState;

	D3D10_DRIVER_TYPE m_dx10DriverType;
	D3DXCOLOR m_clearColor;

	UINT m_nextEffectID;
	std::map<std::string, UINT> m_effectIDs;
	std::map<UINT, ID3D10Effect*> m_effectsByID;

	UINT m_nextTechniqueID;
	std::map<UINT, std::map<std::string, UINT>> m_techniqueIDs;
	std::map<UINT, ID3D10EffectTechnique*> m_techniquesByID;

	UINT m_nextInputLayoutID;
	std::map<UINT, ID3D10InputLayout*> m_inputLayouts;

	UINT m_nextBufferID;
	std::map<UINT, CStaticBuffer*> m_staticBuffers;
};

#endif // __DX10RENDERER_H__

