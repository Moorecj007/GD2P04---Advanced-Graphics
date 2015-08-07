/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.cpp
* Description : The core of the Application is run here. The link between all components.
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Application.h"

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	// Create the Application 
	CApplication pApp = CApplication();
	
	
	if (pApp.CreateWindowApp(1000, 1000, _hInstance) == true)
	{
		VALIDATE(pApp.Initialise());
		pApp.Execute();
	}
	
	// Delete all contents of the Application
	pApp.ShutDown();
	return 0;
}

LRESULT CALLBACK CApplication::WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT paintStruct;		// Used in WM_PAINT.
	HDC hDC;						// Handle to a device context.

	// Switch case dependent on the message sent
	switch (_uiMsg)
	{
	case WM_CREATE:
	{
		return (0);
	}
		break;
	case WM_PAINT:
	{
		hDC = BeginPaint(_hWnd, &paintStruct);	// Prepares the window for painting
		EndPaint(_hWnd, &paintStruct);			// Marks the ending of the window being painted

		return (0);
	}
		break;
	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);
		return (0);
	}
		break;
	default: break;
	} // End switch.

	// Process any messages left to process
	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

bool CApplication::CreateWindowApp(int _clientWidth, int _clientHeight, HINSTANCE _hInstance)
{
	WNDCLASSEX winClass;	// This will hold the class we create.

	// Fills in the window class structure.
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = _hInstance;
	winClass.hIcon = NULL;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)BLACK_BRUSH;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOW_CLASS_NAME;
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registers the window class
	VALIDATE(RegisterClassEx(&winClass));

	m_hWnd = CreateWindowEx(NULL,								// Extended style.
		WINDOW_CLASS_NAME,					// Class.
		L"DX10 Framework",					// Title.
		WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_SYSMENU,// Windowed Mode
		0, 0,								// Initial x,y position for the top left corner of the window
		_clientWidth, _clientHeight,		// Initial width, height of the window
		NULL,								// Handle to parent.
		NULL,								// Handle to menu.
		_hInstance,							// Instance of this application.
		NULL);								// Extra creation parameters.

	// Check the window was created successfully.
	VALIDATE(m_hWnd);

	return true;
	
}

int CApplication::Execute()
{
	MSG uiMsg;				// Generic message.
	bool bOnline = true;

	// Enter main event loop.
	while (bOnline)
	{
		while (PeekMessage(&uiMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uiMsg);
			DispatchMessage(&uiMsg);
		}

		if (uiMsg.message == WM_QUIT)
		{
			break;
		}

		ExecuteOneFrame(); //remember VIRTUAL
	}

	// Return to Windows
	return (static_cast<int>(uiMsg.wParam));
}

// Constructors / Destructors
CApplication::CApplication()
{

}

bool CApplication::Initialise()
{
	// Create a Renderer for graphics
	m_pRenderer = new CDX10Renderer();
	VALIDATE(m_pRenderer->Initialise(m_clientWidth, m_clientHeight, m_hWnd));

	return true;
}

CApplication::~CApplication()
{
}

void CApplication::ShutDown()
{
	// Delete and free the memory from the Renderer
	m_pRenderer->ShutDown();
	delete m_pRenderer;
	m_pRenderer = 0;
}

void CApplication::ExecuteOneFrame()
{
	// TO DO: remove comment
	//CalculateFPS();
	//Process();
	//PreDraw();
	//Draw();
	//PostDraw();

	m_pRenderer->RenderFrame();
}
















