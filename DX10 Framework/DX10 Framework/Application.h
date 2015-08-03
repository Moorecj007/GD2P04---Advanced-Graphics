/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.h
* Description : TO DO
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once

#pragma comment(lib, "Winmm.lib")
//#pragma comment(lib, "d3d10.lib")
//#pragma comment(lib, "d3dx10d.lib")
//#pragma comment(lib, "dxerr.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "DXGI.lib")

// Defines and Macros
#define WIN32_LEAN_AND_MEAN
#define WINDOW_CLASS_NAME L"DX10 FRAMEWORK"

#ifdef _DEBUG
// Visual Leak Detector to be run only if in DEBUG mode
//#include "vld.h"
#define D3D_DEBUG_INFO
#endif // _DEBUG

// Library Includes
#include <windows.h>

class CApplication
{
public:
	CApplication();
	~CApplication();

	int Execute();

	/***********************
	* WindowProc: Process the window
	* @author: Callan Moore
	* @Parameter: _hWnd: Handle to the Window sending the message
	* @Parameter: _uiMsg: The message ID being sent
	* @Parameter: _wParam: Additional detail about the message being sent
	* @Parameter: _lParam: Additional detail about the message being sent
	* @return: LRESULT: The resulting value
	********************/
	LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);

	/***********************
	* WinMain: TO DO
	* @author: Callan Moore
	* @Parameter: _hInstance: Instance handle that Windows generates for your application
	* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
	* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments
	* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
	* @return: int: Program ends here
	********************/
	int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow);

	HWND CreateWindowApp(int _iScreenWidth, int _iScreenHeight, HINSTANCE _hInstance);
};

