
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

	R.top = R.top + 50;
	mFont->DrawText(0, mTimeStats.c_str(), -1, &R, DT_NOCLIP, BLACK);

	if (mAdapterCount > 0)
	{
		R.top = R.top + 50;
		std::string strAdapters = "Adapter Count: ";
		strAdapters.append(std::to_string(mAdapterCount));
		mFont->DrawTextA(0, strAdapters.c_str(), -1, &R, DT_NOCLIP, BLACK);

		for (UINT i = 0; i < vAdapterInfo.size(); i++)
		{
			R.top = R.top + 25;
			mFont->DrawTextA(0, vAdapterInfo[i].c_str(), -1, &R, DT_NOCLIP, BLACK);
		}
		
		R.top = R.top + 25;
		std::string strOutputs = "Default Adapter Number of Outputs: ";
		strOutputs.append(std::to_string(vAdapterOutputs.size()));
		mFont->DrawTextA(0, strOutputs.c_str(), -1, &R, DT_NOCLIP, BLACK);
		
		for (UINT i = 0; i < vModeDescInfo.size(); i++)
		{
			R.top = R.top + 25;
			mFont->DrawTextA(0, vModeDescInfo[i].c_str(), -1, &R, DT_NOCLIP, BLACK);
		}


	}

	mSwapChain->Present(0, 0);
}
