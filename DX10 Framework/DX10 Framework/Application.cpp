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

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _cmdShow)
{
	int clientWidth = 1000;
	int clientHeight = 1000;

	// Create the Application 
	CApplication* pApp = CApplication::GetInstance();
	
	
	if (pApp->CreateWindowApp(clientWidth, clientHeight, _hInstance) == true)
	{
		VALIDATE(pApp->Initialise(clientWidth, clientHeight));
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

CApplication* CApplication::GetInstance()
{
	if (s_pApp == 0)
	{
		s_pApp = new CApplication();
	}
	return s_pApp;
}

bool CApplication::Initialise(int _clientWidth, int _clientHeight)
{
	m_pTimer = new CTimer();
	m_pTimer->Reset();

	// Save the client window sizes
	m_clientWidth = _clientWidth;
	m_clientHeight = _clientHeight;

	// Create a Renderer for graphics
	m_pRenderer = new CDX10Renderer();
	VALIDATE(m_pRenderer->Initialise(m_clientWidth, m_clientHeight, m_hWnd));

	// Initialise boolean array for KeyDown to false
	m_pKeyDown = new bool[255];
	memset(m_pKeyDown, false, 255);

	// Creating a Cube Object
	m_pCubeMesh = new CMesh_Rect_Prism();
	TVertexColor vertColor;
	v3float scalar(1.0f, 1.0f, 1.0f);
	m_pCubeMesh->Initialise(m_pRenderer, vertColor, scalar, RED);
	m_pCube = new CGeometricObject();
	m_pCube->Initialise(m_pRenderer, m_pCubeMesh);

	// Creating a Terrain Object
	m_pTerrainMesh = new CMesh_Finite_Plane();
	//TVertexColor vertColor;
	scalar = v3float(1.0f, 0.3f, 1.0f);
	m_pTerrainMesh->Initialise(m_pRenderer, vertColor, scalar, RED);
	m_pTerrain = new CGeometricObject();
	m_pTerrain->Initialise(m_pRenderer, m_pTerrainMesh);

	m_pCamera = new CCamera_Debug();
	m_pCamera->Initialise(m_pRenderer);
	m_pCamera->SetSpeed(10);
	m_pCamera->SetPostionVec({ -20.0f, 10.0f, -20.0f });
	m_pCamera->SetTargetVector({ 0.0f, 0.0f, 0.0f });
	


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
	ReleasePtr(m_pCubeMesh);
	ReleasePtr(m_pTerrainMesh);
	ReleasePtr(m_pCube);
	ReleasePtr(m_pTerrain);
	ReleasePtr(m_pTimer);
	ReleasePtr(m_pCamera);

	// Delete and free the memory from the Renderer
	m_pRenderer->ShutDown();
	ReleasePtr(m_pRenderer);
}

void CApplication::ExecuteOneFrame()
{	
	Process();
	Draw();
}

void CApplication::Process()
{
	// Retrieve the Delta Tick of the last frame
	Sleep(1);
	m_pTimer->Tick();
	m_dt = m_pTimer->GetDeltaTime();

	HandleInput();
	m_pCamera->Process();
	m_pCube->Process(m_dt);
	m_pTerrain->Process(m_dt);
}

void CApplication::Draw()
{
	// Get the Renderer Ready to receive new data
	m_pRenderer->StartRender();

	m_pTerrain->Draw();
	m_pCube->Draw();

	// Tell the Renderer the data input is over and present the outcome
	m_pRenderer->EndRender();
}

void CApplication::HandleInput()
{
	// Template Inputs
	if (m_pKeyDown[VK_F1])
	{	
		m_pRenderer->ToggleFullscreen();
		m_pKeyDown[VK_F1] = false;
	}
	if (m_pKeyDown[VK_F2])
	{

		m_pRenderer->ToggleFillMode();
		m_pKeyDown[VK_F2] = false;
	}
	//if (m_pKeyDown[0x57]) // W Key
	//{
	//	m_pCamera->MoveInLookDir(1.0f, m_dt);
	//}
	//if (m_pKeyDown[0x53]) // S Key
	//{
	//	m_pCamera->MoveInLookDir(-1.0f, m_dt);
	//}
	//if (m_pKeyDown[0x41])	// A Key
	//{
	//	m_pCamera->Yaw(1.0f, m_dt);
	//}
	//if (m_pKeyDown[0x44])	// D Key
	//{
	//	m_pCamera->Yaw(-1.0f, m_dt);
	//}

	// Application Specific Inputs
}

void CApplication::SetKeyDown(int _index, bool _down)
{
	m_pKeyDown[_index] = _down;
}
















