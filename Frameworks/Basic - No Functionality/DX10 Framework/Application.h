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
	* CApplication: Default Constructor for Application class
	* @author: Callan Moore
	********************/
	CApplication();

	/***********************
	* Initialise: Initialise the Application
	* @author: Callan Moore
	* @return: bool: Successful or not
	********************/
	bool Initialise();

	/***********************
	* ~CApplication: Default Constructor for Application class
	* @author: Callan Moore
	********************/
	~CApplication();

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

private:
	// Window Variables
	HWND m_hWnd;
	int m_clientWidth;
	int m_clientHeight;

	// Renderer Variables
	CDX10Renderer* m_pRenderer;
};

#endif // __APPLICATION_H__
