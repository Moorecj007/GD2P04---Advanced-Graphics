/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.h
* Description : The core of the Application is run here. The link between all components.
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#pragma comment(lib, "Winmm.lib")

// Defines and Macros
#define WIN32_LEAN_AND_MEAN
#define WINDOW_CLASS_NAME L"DX10 FRAMEWORK"

#ifdef _DEBUG
// Visual Leak Detector to be run only if in DEBUG mode
#include "vld.h"
#define D3D_DEBUG_INFO
#endif // _DEBUG

// Library Includes
#include <windows.h>

// Local Includes
#include "DX10Renderer.h"
#include "GeometricObject.h"
#include "Timer.h"
#include "GeometricMesh.h"
#include "Mesh_Rect_Prism.h"
#include "Mesh_Finite_Plane.h"
#include "Camera_FirstPerson.h"

class CApplication
{
public:
	
	/***********************
	* WindowProc: Process the window
	* @author: Callan Moore
	* @Parameter: _hWnd: Handle to the Window sending the message
	* @Parameter: _uiMsg: The message ID being sent
	* @Parameter: _wParam: Additional detail about the message being sent
	* @Parameter: _lParam: Additional detail about the message being sent
	* @return: LRESULT: The resulting value
	********************/
	static LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);

	/***********************
	* CreateWindowApp: Creates the window for the Application
	* @author: Callan Moore
	* @Parameter: _clientWidth: Width of the screen
	* @Parameter: _clientHeight: Height of the screen
	* @Parameter: _hInstance: The instance of the application
	* @return: bool: Successful or not
	********************/
	bool CreateWindowApp(int _clientWidth, int _clientHeight, HINSTANCE _hInstance);

	/***********************
	* Execute: Runs the main loop of the Application
	* @author: Callan Moore
	* @return: int: Integer containing details about the last message resulting it termination
	********************/
	int Execute();

	// Constructors / Destructors
	/***********************
	* GetInstance: Returns the singleton instance of the Application, if it doesn't exist creates it.
	* @author: Callan Moore
	* @return: CApplication*: The current instance of the Application
	********************/
	static CApplication* GetInstance();
	
	/***********************
	* Initialise: Initialise the Application
	* @author: Callan Moore
	* @parameter: _clientWidth: Width of the client window
	* @parameter: _clientHeight: Height of the client window
	* @Parameter: _hInstance: Handle to the current instance
	* @return: bool: Successful or not
	********************/
	bool Initialise(int _clientWidth, int _clientHeight, HINSTANCE _hInstance);

	/***********************
	* ~CApplication: Default Destructor for Application class
	* @author: Callan Moore
	********************/
	~CApplication();

	/***********************
	* DestroyInstance: Deletes the instance of the Application.
	* @author: Callan Moore
	* @return: void
	********************/
	static void DestroyInstance();

	/***********************
	* ShutDown: Shuts down and releases all memory created by Application
	* @author: Callan Moore
	* @return: void
	********************/
	void ShutDown();

	/***********************
	* ExecuteOneFrame: Executes one frame of the Application
	* @author: Callan Moore
	* @return: void
	********************/
	void ExecuteOneFrame();

	/***********************
	* Process: Process the Application
	* @author: Callan Moore
	* @return: void
	********************/
	void Process();

	/***********************
	* Draw: Draw the Application components
	* @author: Callan Moore
	* @return: void
	********************/
	void Draw();

	/***********************
	* HandleInput: Handle all input for the application
	* @author: Callan Moore
	* @return: void
	********************/
	void HandleInput();

	/***********************
	* SetKeyDown: Sets the Key down boolean for input Key
	* @author: Callan Moore
	* @parameter: _index: Index of the Key to set
	* @parameter: _down: True/false setting
	* @return: void
	********************/
	void SetKeyDown(int _index, bool _down);

private:
	// Preventing copies and extra constructions
	CApplication();
	CApplication(const CApplication& _kr);
	CApplication& operator= (const CApplication& _kr);

private:
	// Singleton Instance
	static CApplication* s_pApp;

	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;
	bool m_online;

	// Timer Variables
	CTimer* m_pTimer;
	float m_dt;

	// Input Variables
	bool* m_pKeyDown;

	// Renderer Variables
	CDX10Renderer* m_pRenderer;

	// Objects
	CGeometricObject* m_pCube;
	CGeometricObject* m_pTerrain;

	// Meshes
	CGeometricMesh* m_pCubeMesh;
	CGeometricMesh* m_pTerrainMesh;

	// Camera
	CCamera_FirstPerson* m_pCamera;
	// Mouse Tracking
	POINT m_mousePrev;
	bool m_mouseMoveLeft;
	bool m_mouseMoveRight;
	bool m_mouseMoveUp;
	bool m_mouseMoveDown;
};

#endif // __APPLICATION_H__

