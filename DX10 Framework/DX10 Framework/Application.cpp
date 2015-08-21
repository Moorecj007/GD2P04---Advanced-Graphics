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

// Static Variables
CApplication* CApplication::s_pApp = 0;

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _cmdShow){
	int clientWidth = 1000;
	int clientHeight = 1000;

	// Create the Application 
	CApplication* pApp = CApplication::GetInstance();
	
	
	if (pApp->CreateWindowApp(clientWidth, clientHeight, _hInstance) == true)
	{
		VALIDATE(pApp->Initialise(clientWidth, clientHeight, _hInstance));
		pApp->Execute();
	}
	
	// Delete all contents of the Application
	pApp->DestroyInstance();
	return 0;
}

LRESULT CALLBACK CApplication::WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	// Retrieve the Instance of the Application
	CApplication* pApp = CApplication::GetInstance();

	// Switch case dependent on the message sent
	switch (_uiMsg)
	{
		case WM_DESTROY:	// Fall Through
		case WM_CLOSE:
		{
			// Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);	
		}
		break;
		case WM_KEYDOWN:
		{
			// Only accepts the input once per key press
			if (((_lParam >> 30) & 1) != 1)
			{
				pApp->SetKeyDown(_wParam, true);
			}
		}
		break;
		case WM_KEYUP:
		{
			pApp->SetKeyDown(_wParam, false);
		}
		break;
		case WM_MOUSEMOVE:
		{
			
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
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)WHITE_BRUSH;
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

	// Enter main event loop.
	while (m_online)
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

		ExecuteOneFrame();
	}

	// Return to Windows
	return (static_cast<int>(uiMsg.wParam));
}

// Constructors / Destructors
CApplication::CApplication()
{

}

CApplication* CApplication::GetInstance()
{
	if (s_pApp == 0)
	{
		s_pApp = new CApplication();
	}
	return s_pApp;
}

bool CApplication::Initialise(int _clientWidth, int _clientHeight, HINSTANCE _hInstance)
{
	// Determine which rendererer to use
	bool usingDX10Renderer = true;
	bool usingGDIRenderer = false;

	// default state so only one renderer can be active at any time
	if (usingDX10Renderer == usingGDIRenderer)
	{
		usingDX10Renderer = true;
		usingGDIRenderer = false;
	}

	m_online = true;
	m_pTimer = new CTimer();
	m_pTimer->Reset();

	// Save the client window sizes
	m_clientWidth = _clientWidth;
	m_clientHeight = _clientHeight;

	// Initialise boolean array for KeyDown to false
	m_pKeyDown = new bool[255];
	memset(m_pKeyDown, false, 255);

	// Create a Renderer for graphics
	if (usingDX10Renderer == true)
	{
		// Initialise the Renderer
		m_pDX10Renderer = new CDX10Renderer();
		VALIDATE(m_pDX10Renderer->Initialise(m_clientWidth, m_clientHeight, m_hWnd));

		// Initialise the Objects
		m_pCamera = new CCamera_FirstPerson();
		m_pCamera->Initialise(m_pDX10Renderer, _hInstance, m_hWnd);

		TVertexColorNormalUV vert;
		m_pCubeMesh = new CMesh_Rect_Prism();
		VALIDATE(m_pCubeMesh->Initialise(m_pDX10Renderer, vert, { 2.0f, 2.0f, 2.0f }));

		m_pCube = new DX10_Color_Obj();
		VALIDATE(m_pCube->Initialise(m_pDX10Renderer, m_pCubeMesh, BLUE));
	}

	if (usingGDIRenderer == true)
	{
		// Initialise the Renderer
		m_pGDIRenderer = new CGDI_Renderer();
		VALIDATE(m_pGDIRenderer->Initialise(m_hWnd, _hInstance, m_clientWidth, m_clientHeight));

		// Initialise the Objects
		m_pQuad = new CGDI_Quad();
		VALIDATE(m_pQuad->Initialise(m_pGDIRenderer, { 400, 400 }, 70, 5, RGB(255, 0, 0)));
		m_pQuad2 = new CGDI_Quad();
		VALIDATE(m_pQuad2->Initialise(m_pGDIRenderer, { 200, 600 }, 100, 100, 0x00FF00));
		m_pQuad3 = new CGDI_Quad();
		VALIDATE(m_pQuad3->Initialise(m_pGDIRenderer, { 800, 700 }, 20, 40, 0x0000FF));
	}
	
	return true;
}

CApplication::~CApplication()
{
}

void CApplication::DestroyInstance()
{
	s_pApp->ShutDown();
	delete s_pApp;
	s_pApp = 0;
}

void CApplication::ShutDown()
{
	// Delete and free memory for the Application variables
	ReleasePtr(m_pKeyDown);
	ReleasePtr(m_pTimer);

	ReleasePtr(m_pCamera);
	ReleasePtr(m_pCubeMesh);
	ReleasePtr(m_pCube);

	ReleasePtr(m_pQuad);
	ReleasePtr(m_pQuad2);
	ReleasePtr(m_pQuad3);

	// Delete and free the memory from the Renderer
	if (m_pDX10Renderer != 0)
	{
		m_pDX10Renderer->ShutDown();
	}
	ReleasePtr(m_pDX10Renderer);
	ReleasePtr(m_pGDIRenderer);
}

void CApplication::ExecuteOneFrame()
{	
	Process();
	Draw();
}

void CApplication::Process()
{
	// Retrieve the Delta Tick of the last frame
	//Sleep(1);
	m_pTimer->Tick();
	m_dt = m_pTimer->GetDeltaTime();

	HandleInput();

	if (m_pDX10Renderer != 0)
	{
		m_pCamera->Process(m_dt);
		m_pCube->Process(m_dt);
	}

	if (m_pGDIRenderer != 0)
	{

	}
}

void CApplication::Draw()
{
	if (m_pDX10Renderer != 0)
	{
		// Get the Renderer Ready to receive new data
		m_pDX10Renderer->StartRender();

		m_pCube->Draw();

		// Tell the Renderer the data input is over and present the outcome
		m_pDX10Renderer->EndRender();
	}

	if (m_pGDIRenderer != 0)
	{
		m_pGDIRenderer->BeginRender();

		m_pQuad->Render();
		m_pQuad2->Render();
		m_pQuad3->Render();

		m_pGDIRenderer->EndRender();
	}
}

void CApplication::HandleInput()
{
	// Template Inputs
	if (m_pKeyDown[VK_F1])
	{	
		m_pDX10Renderer->ToggleFullscreen();
		m_pKeyDown[VK_F1] = false;
	}
	if (m_pKeyDown[VK_F2])
	{
		m_pDX10Renderer->ToggleFillMode();
		m_pKeyDown[VK_F2] = false;
	}
	if (m_pKeyDown[VK_ESCAPE])
	{
		if (m_pDX10Renderer != 0)
		{
			if (m_pDX10Renderer->GetFullScreenState() == true)
			{
				m_pDX10Renderer->ToggleFullscreen();
			}
		}
		m_online = false;
	}

	// Camera Inputs
	if (m_pKeyDown[0x57]) // W Key
	{
		m_pCamera->MoveForwards(1.0f);
	}
	if (m_pKeyDown[0x53]) // S Key
	{
		m_pCamera->MoveForwards(-1.0f);
	}
	if (m_pKeyDown[0x41])	// A Key
	{
		m_pCamera->Strafe(-1.0f);
	}
	if (m_pKeyDown[0x44])	// D Key
	{
		m_pCamera->Strafe(1.0f);
	}
	if (m_pKeyDown[0x45])	// E Key
	{
		m_pCamera->Fly(1.0f);
	}
	if (m_pKeyDown[0x51])	// Q Key
	{
		m_pCamera->Fly(-1.0f);
	}
}

void CApplication::SetKeyDown(int _index, bool _down)
{
	m_pKeyDown[_index] = _down;
}
















