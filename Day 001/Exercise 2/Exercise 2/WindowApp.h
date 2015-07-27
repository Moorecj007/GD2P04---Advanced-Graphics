#ifndef WINDOWAPP_H
#define WINDOWAP_H

#include <Windows.h>
#include "Utility.h"
#include "Timer.h"
#include <string>
#include <vector>



class WindowApp
{
public:
	WindowApp(HINSTANCE hInstance);
	virtual ~WindowApp();

	HINSTANCE getAppInst();
	HWND      getMainWnd();

	int run();
	void ToggleFullScreen();

	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual void initApp();
	virtual void onResize();// reset projection/etc
	virtual void updateScene(float dt);
	virtual void drawScene(); 
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void DetectAdapters();

protected:
	void initMainWindow();
	void initDirect3D();
	
protected:

	HINSTANCE mhAppInst;
	HWND      mhMainWnd;
	bool      mAppPaused;
	bool      mMinimized;
	bool      mMaximized;
	bool      mResizing;
	bool	  mFullscreen;

	Timer mTimer;

	std::wstring mFrameStats;
	std::wstring mTimeStats;
	UINT mAdapterCount;
	std::vector <IDXGIAdapter*> vAdapters;
	std::vector <bool> vAdaptersSupported;
	std::vector <IDXGIOutput*> vAdapterOutputs;
	std::vector <DXGI_MODE_DESC*> vModeDesc;
	std::vector <std::string> vModeDescInfo;
	std::vector <std::string> vAdapterInfo;
 
	ID3D10Device*    md3dDevice;
	IDXGISwapChain*  mSwapChain;
	ID3D10Texture2D* mDepthStencilBuffer;
	ID3D10RenderTargetView* mRenderTargetView;
	ID3D10DepthStencilView* mDepthStencilView;
	ID3DX10Font* mFont;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	D3D10_DRIVER_TYPE md3dDriverType;
	D3DXCOLOR mClearColor;
	int mClientWidth;
	int mClientHeight;
};




#endif