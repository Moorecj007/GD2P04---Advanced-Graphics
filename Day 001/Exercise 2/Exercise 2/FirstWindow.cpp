
//#pragma comment(lib, "d3d10.lib")
//#pragma comment(lib, "d3dx10d.lib")
//#pragma comment(lib, "dxerr.lib")
//#pragma comment(lib, "dxguid.lib")

#include "WindowApp.h"
 
class InitDirect3DApp : public WindowApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene(); 
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif


	InitDirect3DApp theApp(hInstance);
	
	theApp.initApp();

	return theApp.run();
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: WindowApp(hInstance) 
{
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( md3dDevice )
		md3dDevice->ClearState();
}

void InitDirect3DApp::initApp()
{
	WindowApp::initApp();
}

void InitDirect3DApp::onResize()
{
	WindowApp::onResize();
}

void InitDirect3DApp::updateScene(float dt)
{
	WindowApp::updateScene(dt);
}

void InitDirect3DApp::drawScene()
{
	WindowApp::drawScene();

	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = {5, 5, 0, 0};
	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, BLACK);

	mSwapChain->Present(0, 0);
}
